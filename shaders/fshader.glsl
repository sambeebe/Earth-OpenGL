#version 150

uniform vec4 ambient;
uniform vec4 LightPosition;

in vec4 pos;
in vec4 N;
in vec2 texCoord;

uniform mat4 ModelViewLight;


uniform sampler2D textureEarth;
uniform sampler2D textureNight;
uniform sampler2D textureCloud;
uniform sampler2D texturePerlin;
uniform sampler2D texture_R2D2_Diffuse;
//uniform sampler2D texture_bb1;
//uniform sampler2D texture_bb2;
uniform float animate_time;
uniform int earth_draw;


out vec4 fragColor;


void main()
{
    vec4 tex_color;
    vec4 L;
    vec4 diffuse;
    if (earth_draw == 1){
   
    vec4 perlin_tex = texture(texturePerlin, texCoord );
    vec4 luma = vec4(0.57299, 0.587, 0.114, .4);
    float power = dot(perlin_tex, luma);
    power = sin(3.1415927*1.0 * mod(power + animate_time * 0.13, 1.0));
    perlin_tex = texture(texturePerlin, texCoord * power);

  vec4 tex_color1 = texture(textureCloud , texCoord );
  vec4 tex_color2 = texture(textureEarth , texCoord );
  vec4 night_color = texture(textureNight, texCoord );

   tex_color = clamp(tex_color1 + tex_color2 + perlin_tex, 0.,1.);
  tex_color = mix(tex_color, night_color, sin(animate_time));
  tex_color = clamp(tex_color, 0., 1.);
  float nighttime = clamp(cos(animate_time), .1, .5);
  L = normalize( (ModelViewLight*vec4(sin(animate_time) * 100. , 0., cos(animate_time) * 100., 1.)) - pos );
  diffuse =  max(dot(N, L), 0.) + vec4(.351,.351,.351,1.) ;
  diffuse =  clamp(diffuse, 0.0, 1.0);
  fragColor =  diffuse * tex_color ;
  fragColor = clamp(fragColor, 0.0, 1.0);
  fragColor.a = 1.0;
    }
    else{
        tex_color = texture(texture_R2D2_Diffuse, texCoord );
        fragColor = tex_color;
          fragColor = clamp(fragColor, 0.0, 1.0);
          fragColor.a = 1.0;
//         L = normalize( (ModelViewLight*LightPosition) - pos );
//         diffuse =  max(dot(N, L), 0.) + vec4(.81,.81,.81,1.) ;

    }
   

//  diffuse = clamp(diffuse, 0.0, 1.0);
//  fragColor =  diffuse * tex_color ;
//  fragColor = clamp(fragColor, 0.0, 1.0);
//  fragColor.a = 1.0;
}


