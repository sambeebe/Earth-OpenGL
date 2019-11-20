#include "common.h"
#include "SourcePath.h"


using namespace Angel;

typedef vec4 color4;

//lighting parameters
vec4 light_position( 0.0, 0.0, 10.10800010, 1.0 );
vec4 ambient(  .10, 0.10, 0.10, 1.0 );

Mesh *earth_mesh;

//OpenGL draw variables

std::vector < GLuint > vao;
GLuint earth_vao;
GLuint earth_buffer;

std::vector < GLuint > buffer;
std::vector < Mesh > mesh;
GLuint  ModelViewEarth, ModelViewLight, NormalMatrix, Projection;
bool wireframe;
GLuint program;

//Trackball movement
Trackball tb;

// Texture objects references
GLuint month_texture;
GLuint night_texture;
GLuint cloud_texture;
GLuint perlin_texture;
GLuint r2d2_texture;
GLuint bb8_texture1;
GLuint bb8_texture2;
int current_draw;
int earth_draw = 1;
int tex_draw = 1;
//Animation variables
float animate_time;
float rotation_angle;

enum{ R2D2,  _TOTAL_MODELS};
std::string files[_TOTAL_MODELS] = {


    "/models/R2D2_Standing.obj"
//    "/models/Tie_Fighter.obj"
    
};

void loadFreeImageTexture(const char* lpszPathName, GLuint textureID, GLuint GLtex){
    
    FreeImage_Initialise();
    
    int X,Y;
    uint8_t *Dst, *Src;
    FIBITMAP*         bitmap=0;
    BITMAPINFO*       info=0;
    FREE_IMAGE_FORMAT fif;
    BYTE*             bits=0;
    int               width,height,bpp,pitch;
    FREE_IMAGE_TYPE   format;
    
    fif = FreeImage_GetFileType(lpszPathName, 0);
    if(fif == FIF_UNKNOWN) {fif = FreeImage_GetFIFFromFilename(lpszPathName);}
    if(fif == FIF_UNKNOWN || !FreeImage_FIFSupportsReading(fif) || !(bitmap = FreeImage_Load(fif, lpszPathName, 0))){
        std::cout << "FreeImage: Unknown image type\n";
    }
    
    info   = FreeImage_GetInfo(bitmap);
    bits   = FreeImage_GetBits      (bitmap);
    width  = FreeImage_GetWidth     (bitmap);
    height = FreeImage_GetHeight    (bitmap);
    bpp    = FreeImage_GetBPP       (bitmap);
    pitch  = FreeImage_GetPitch     (bitmap);
    format = FreeImage_GetImageType (bitmap);
    
    //handle only supported FreeImage
    if((bits == 0) || (width == 0) || (height == 0) || (format!=FIT_BITMAP && format != FIT_UINT16)){
        FreeImage_Unload(bitmap);
        std::cout << "FreeImage: Cannot load image file\n";
    }
    
    GLint GL_format = GL_RGB;
    
    //handle only GRAY, RGB and RGBA
    if (bpp!=8 && bpp!=24 && bpp!=32){
        FreeImage_Unload(bitmap);
        std::cout << "FreeImage: Only supports GRAY, RGB and RGBA\n";
    }else{
        switch(bpp){
            case 8:
                GL_format = GL_LUMINANCE;
                break;
            case 24:
                GL_format = GL_RGB;
                break;
            case 32:
                GL_format = GL_RGBA;
                break;
        }
    }
    
    std::cout << "Image " << lpszPathName << ": " << width << " X " << height << ": " << bpp << " bits\n";
    
    int buffersize  =width*height*(bpp/8);
    uint8_t *buffer = new uint8_t[buffersize];
    
    //fill the buffers
    int step = bpp/8;
    Dst = (uint8_t *)buffer;
    int pixel = 0;
    
    for (Y=height-1;Y>=0;Y--)
    {
        Src=bits+pitch*Y;
        
        for (X=0;X<width;X++,Src+=step,Dst+=(bpp/8),pixel++)
        {
            if (bpp==8)
            {
                Dst[0]=Src[0];
            }
            else
            {Dst[0]=Src[FI_RGBA_RED];Dst[1]=Src[FI_RGBA_GREEN];Dst[2]=Src[FI_RGBA_BLUE];
                if (bpp==32){ Dst[3]=Src[FI_RGBA_ALPHA]; }
            }
        }
    }
    
    glActiveTexture( GLtex );
    glBindTexture( GL_TEXTURE_2D, textureID );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_format, width, height, 0, GL_format, GL_UNSIGNED_BYTE, buffer );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glGenerateMipmap(GL_TEXTURE_2D);
    
    //Put things away and free memory
    delete[] buffer;
    FreeImage_Unload(bitmap);
    FreeImage_DeInitialise();
    
}


static void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}

//User interaction handler
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
     current_draw = (current_draw+1)%_TOTAL_MODELS;
  }
    if (key == GLFW_KEY_E && action == GLFW_PRESS){
        earth_draw = 1;
          tex_draw = 1;
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS){
        earth_draw = 0;
            tex_draw = 0;
    }
    if (key == GLFW_KEY_Q && action == GLFW_PRESS){
        tex_draw = 1;
    }
    if (key == GLFW_KEY_W && action == GLFW_PRESS){
        tex_draw = 0;
    }

}

//User interaction handler
static void mouse_click(GLFWwindow* window, int button, int action, int mods){
  
  if (GLFW_RELEASE == action){
    tb.moving=tb.scaling=tb.panning=false;
    return;
  }
  
  if( mods & GLFW_MOD_SHIFT){
    tb.scaling=true;
  }else if( mods & GLFW_MOD_ALT ){
    tb.panning=true;
  }else{
    tb.moving=true;
    Trackball::trackball(tb.lastquat, 0, 0, 0, 0);
  }
  
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  tb.beginx = xpos; tb.beginy = ypos;
}

//User interaction handler
void mouse_move(GLFWwindow* window, double x, double y){
  
  int W, H;
  glfwGetFramebufferSize(window, &W, &H);

  
  float dx=(x-tb.beginx)/(float)W;
  float dy=(tb.beginy-y)/(float)H;
  
  if (tb.panning)
    {
    tb.ortho_x  +=dx;
    tb.ortho_y  +=dy;
    
    tb.beginx = x; tb.beginy = y;
    return;
    }
  else if (tb.scaling)
    {
    tb.scalefactor *= (1.0f+dx);
    
    tb.beginx = x;tb.beginy = y;
    return;
    }
  else if (tb.moving)
    {
    Trackball::trackball(tb.lastquat,
              (2.0f * tb.beginx - W) / W,
              (H - 2.0f * tb.beginy) / H,
              (2.0f * x - W) / W,
              (H - 2.0f * y) / H
              );
    
    Trackball::add_quats(tb.lastquat, tb.curquat, tb.curquat);
    Trackball::build_rotmatrix(tb.curmat, tb.curquat);
    
    tb.beginx = x;tb.beginy = y;
    return;
    }
}

float map2(float Input, float InputLow, float InputHigh, float OutputLow, float OutputHigh ){
    return ((Input - InputLow) / (InputHigh - InputLow)) * (OutputHigh - OutputLow) + OutputLow;
}

void init(){
  
  std::string vshader = source_path + "/shaders/vshader.glsl";
  std::string fshader = source_path + "/shaders/fshader.glsl";
  
  GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
  GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, (const GLchar**) &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);
  check_shader_compilation(vshader, vertex_shader);
  
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, (const GLchar**) &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);
  check_shader_compilation(fshader, fragment_shader);
  
  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  
  glLinkProgram(program);
  check_program_link(program);
  
  glUseProgram(program);
  
  glBindFragDataLocation(program, 0, "fragColor");

  //Per vertex attributes
  GLuint vPosition = glGetAttribLocation( program, "vPosition" );
  GLuint vNormal   = glGetAttribLocation( program, "vNormal" );
  GLuint vTexCoord = glGetAttribLocation( program, "vTexCoord" );
  
  //Retrieve and set uniform variables
  glUniform4fv( glGetUniformLocation(program, "LightPosition"), 1, light_position);
  glUniform4fv( glGetUniformLocation(program, "ambient"), 1, ambient );
  
  //Matrix uniform variable locations
  ModelViewEarth = glGetUniformLocation( program, "ModelViewEarth" );
  ModelViewLight = glGetUniformLocation( program, "ModelViewLight" );
  NormalMatrix   = glGetUniformLocation( program, "NormalMatrix" );
  Projection     = glGetUniformLocation( program, "Projection" );
  
  //===== Send data to GPU ======
    glGenVertexArrays( 1, &earth_vao );
    glGenBuffers( 1, &earth_buffer);
    
    vao.resize(_TOTAL_MODELS);
    glGenVertexArrays( _TOTAL_MODELS, &vao[0] );
    
    buffer.resize(_TOTAL_MODELS);
    glGenBuffers( _TOTAL_MODELS, &buffer[0] );
    
    glGenTextures( 1, &month_texture );
    glGenTextures( 1, &night_texture );
    glGenTextures( 1, &cloud_texture );
    glGenTextures( 1, &perlin_texture);
    glGenTextures( 1, &r2d2_texture);
    glGenTextures( 1, &bb8_texture1);
    glGenTextures( 1, &bb8_texture2);
    //[current_draw]
    std::string earth_img = source_path + "/images/world.200405.3.jpg";
    loadFreeImageTexture(earth_img.c_str(), month_texture, GL_TEXTURE0);
    glUniform1i( glGetUniformLocation(program, "textureEarth"), 0 );
    
    std::string cloud_img = source_path + "/images/cloud_combined.jpg";
    loadFreeImageTexture(cloud_img.c_str(), cloud_texture, GL_TEXTURE1);
    glUniform1i( glGetUniformLocation(program, "textureCloud"), 1 );
    
    std::string night_img = source_path + "/images/BlackMarble.jpg";
    loadFreeImageTexture(night_img.c_str(), night_texture, GL_TEXTURE2);
    glUniform1i( glGetUniformLocation(program, "textureNight"), 2 );
    
    std::string perlin_img = source_path + "/images/perlin_noise.jpg";
    loadFreeImageTexture(perlin_img.c_str(), perlin_texture, GL_TEXTURE3);
    glUniform1i( glGetUniformLocation(program, "texturePerlin"), 3 );
    
    std::string r2d2_img = source_path + "/images/R2D2_Diffuse.png";
    loadFreeImageTexture(r2d2_img.c_str(), r2d2_texture, GL_TEXTURE4 );
    glUniform1i( glGetUniformLocation(program, "texture_R2D2_Diffuse"), 4 );
    
//    std::string bb8_img1 = source_path + "/images/BB8_Head_Diffuse.png";
//    loadFreeImageTexture(bb8_img1.c_str(), r2d2_texture, GL_TEXTURE5 );
//    glUniform1i( glGetUniformLocation(program, "bb8_texture1"), 5 );
//    
//    std::string bb8_img2 = source_path + "/images/BB8_Body_Diffuse.png";
//    loadFreeImageTexture(bb8_img2.c_str(), r2d2_texture, GL_TEXTURE6 );
//    glUniform1i( glGetUniformLocation(program, "bb8_texture2"), 6 );
    
//    glActiveTexture( GL_TEXTURE0 );
//    glBindTexture( GL_TEXTURE_2D, month_texture );
//
//    glActiveTexture( GL_TEXTURE1);
//    glBindTexture( GL_TEXTURE_2D, cloud_texture );
//
//    glActiveTexture( GL_TEXTURE2);
//    glBindTexture( GL_TEXTURE_2D, night_texture );
//
//    glActiveTexture( GL_TEXTURE3);
//    glBindTexture( GL_TEXTURE_2D, perlin_texture );
//
//    glActiveTexture( GL_TEXTURE4);
//    glBindTexture( GL_TEXTURE_2D, r2d2_texture );
    
    for(unsigned int i=0; i < _TOTAL_MODELS; i++){
        mesh.push_back((source_path + files[i]).c_str());
        glBindVertexArray( vao[i] );
        glBindBuffer( GL_ARRAY_BUFFER, buffer[i] );
        unsigned int vertices_bytes = mesh[i].vertices.size()*sizeof(vec4);
        unsigned int normals_bytes  = mesh[i].normals.size()*sizeof(vec3);
        unsigned int uv_bytes =  mesh[i].uvs.size()*sizeof(vec2);
        glBufferData( GL_ARRAY_BUFFER, vertices_bytes + normals_bytes + uv_bytes, NULL, GL_STATIC_DRAW );
        unsigned int offset = 0;
        glBufferSubData( GL_ARRAY_BUFFER, offset, vertices_bytes, &mesh[i].vertices[0] );
        offset += vertices_bytes;
        glBufferSubData( GL_ARRAY_BUFFER, offset, normals_bytes,  &mesh[i].normals[0] );
        offset += normals_bytes;
        glBufferSubData( GL_ARRAY_BUFFER, offset, uv_bytes,  &mesh[i].uvs[0] );
        glEnableVertexAttribArray( vNormal );
        glEnableVertexAttribArray( vPosition );
        glEnableVertexAttribArray( vTexCoord );
        glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
        glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(mesh[i].vertices.size()*sizeof(vec4)) );
//        glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices_bytes) );

        glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices_bytes+normals_bytes) );
    }
  earth_mesh = new Mesh();
  earth_mesh->makeSphere(32);
//

    
  //TODO: ADD CLOUD TEXTURE
  
  //TODO: ADD NOISE TEXTURE

  glBindVertexArray( earth_vao );
  glBindBuffer( GL_ARRAY_BUFFER, earth_buffer);
    unsigned int vertices_bytes = earth_mesh->vertices.size()*sizeof(vec4);
    unsigned int normals_bytes  = earth_mesh->normals.size()*sizeof(vec3);
    unsigned int uv_bytes =  earth_mesh->uvs.size()*sizeof(vec2);

  glBufferData( GL_ARRAY_BUFFER, vertices_bytes + normals_bytes+uv_bytes, NULL, GL_STATIC_DRAW );
  unsigned int offset = 0;
    glBufferSubData( GL_ARRAY_BUFFER, offset, vertices_bytes, &earth_mesh->vertices[0] );
  offset += vertices_bytes;
    glBufferSubData( GL_ARRAY_BUFFER, offset, normals_bytes,  &earth_mesh->normals[0] );
  offset += normals_bytes;
    glBufferSubData( GL_ARRAY_BUFFER, offset, uv_bytes,  &earth_mesh->uvs[0] );
//
  glEnableVertexAttribArray( vNormal );
  glEnableVertexAttribArray( vPosition );
  glEnableVertexAttribArray( vTexCoord );

//
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices_bytes) );
  glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices_bytes+normals_bytes) );

  //===== End: Send data to GPU ======


  // ====== Enable some opengl capabilitions ======
  glEnable( GL_DEPTH_TEST );
  glShadeModel(GL_SMOOTH);
  glClearColor( 0.0, 0.0, 0.0, 1.0 );
  
  
  //===== Initalize some program state variables ======
  animate_time = 0.0;
  rotation_angle = 0.0;
  wireframe = false;
  //===== End: Initalize some program state variables ======

}

void animate(){
  //Do 30 times per second
  if(glfwGetTime() > (1.0/60.0)){

    animate_time = animate_time + 0.0001;
    rotation_angle  = rotation_angle + 0.25;


  }
}

void drawObject(GLFWwindow* window){
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    GLfloat aspect = GLfloat(width)/height;
    
    //Projection matrix
    mat4  projection = Perspective( 45.0, aspect, 0.1, 5.0 );
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //"Camera" position
    const vec3 viewer_pos( 0.0, 0.0, 3.0 );
    
    //Track_ball rotation matrix
    mat4 track_ball =  mat4(tb.curmat[0][0], tb.curmat[1][0], tb.curmat[2][0], tb.curmat[3][0],
                            tb.curmat[0][1], tb.curmat[1][1], tb.curmat[2][1], tb.curmat[3][1],
                            tb.curmat[0][2], tb.curmat[1][2], tb.curmat[2][2], tb.curmat[3][2],
                            tb.curmat[0][3], tb.curmat[1][3], tb.curmat[2][3], tb.curmat[3][3]);
    
    //Modelview based on user interaction
    mat4 user_MV  =  Translate( -viewer_pos ) *                    //Move Camera Back to -viewer_pos
    Translate(tb.ortho_x, tb.ortho_y, 0.0) *      //Pan Camera
    track_ball *                                  //Rotate Camera
    Scale(tb.scalefactor,tb.scalefactor,tb.scalefactor);   //User Scale
  
    animate();
    glUniform1f( glGetUniformLocation(program, "animate_time"),   map2((glfwGetTime()), -1., 1., 0., 1.));
    glUniform1i( glGetUniformLocation(program, "earth_draw"),   tex_draw);
    // ====== Draw ======
    if (earth_draw == 1){
    glBindVertexArray(earth_vao);
//


        
    glUniform4fv( glGetUniformLocation(program, "LightPosition"), 1, light_position);
    glUniformMatrix4fv( ModelViewEarth, 1, GL_TRUE, user_MV*earth_mesh->model_view);
    glUniformMatrix4fv( ModelViewLight, 1, GL_TRUE, user_MV*earth_mesh->model_view);
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
    glUniformMatrix4fv( NormalMatrix, 1, GL_TRUE, transpose(invert(user_MV*earth_mesh->model_view)));

    glDrawArrays( GL_TRIANGLES, 0, earth_mesh->vertices.size() );
    }
    else{
    // ====== End: Draw ======
    
    // ====== Draw ======
    
    glBindVertexArray(vao[current_draw]);
    //glBindBuffer( GL_ARRAY_BUFFER, buffer[current_draw] );

    //    glUniformMatrix4fv( ModelView_loc, 1, GL_TRUE, user_MV*mesh[current_draw].model_view);
    //    glUniformMatrix4fv( Projection_loc, 1, GL_TRUE, projection );
    //    glUniformMatrix4fv( NormalMatrix_loc, 1, GL_TRUE, transpose(invert(user_MV*mesh[current_draw].model_view)));
    //Retrieve and set uniform variables
    glUniform4fv( glGetUniformLocation(program, "LightPosition"), 1, light_position);
//    glUniform4fv( glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product  );
//    glUniform4fv( glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product );
//    glUniform4fv( glGetUniformLocation(program, "SpecularProduct"), 1, specular_product );
////    glUniform1f(  glGetUniformLocation(program, "Shininess"), material_shininess );
    glUniformMatrix4fv( ModelViewEarth, 1, GL_TRUE, user_MV*mesh[current_draw].model_view);
     glUniformMatrix4fv( ModelViewLight, 1, GL_TRUE, user_MV*mesh[current_draw].model_view);
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
    glUniformMatrix4fv( NormalMatrix, 1, GL_TRUE, transpose(invert(user_MV*mesh[current_draw].model_view)));

    glDrawArrays( GL_TRIANGLES, 0, mesh[current_draw].vertices.size() );
    }
//     ====== End: Draw ======
}

int main(void){
  
  GLFWwindow* window;
  
  glfwSetErrorCallback(error_callback);
  
  if (!glfwInit())
    exit(EXIT_FAILURE);
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  glfwWindowHint(GLFW_SAMPLES, 4);
  
  window = glfwCreateWindow(1024, 1024, "Tulane Earth", NULL, NULL);
  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  
  //Set key and mouse callback functions
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_click);
  glfwSetCursorPosCallback(window, mouse_move);

  
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  glfwSwapInterval(1);
  
  init();
  
  while (!glfwWindowShouldClose(window)){
    
    //Display as wirfram, boolean tied to keystoke 'w'
    if(wireframe){
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }else{
      glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
      drawObject(window);


    
    glfwSwapBuffers(window);
    glfwPollEvents();
    
  }
//  delete mesh;
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
