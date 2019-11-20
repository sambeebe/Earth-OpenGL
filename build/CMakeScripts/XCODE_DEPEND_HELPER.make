# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.earth.Debug:
PostBuild.glfw.Debug: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Debug/earth.app/Contents/MacOS/earth
PostBuild.glad.Debug: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Debug/earth.app/Contents/MacOS/earth
PostBuild.FreeImage.Debug: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Debug/earth.app/Contents/MacOS/earth
PostBuild.glad.Debug: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Debug/earth.app/Contents/MacOS/earth
PostBuild.glfw.Debug: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Debug/earth.app/Contents/MacOS/earth
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Debug/earth.app/Contents/MacOS/earth:\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/Debug/libglfw3.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Debug/libglad.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/Debug/libFreeImage.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Debug/libglad.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/Debug/libglfw3.a
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Debug/earth.app/Contents/MacOS/earth


PostBuild.glad.Debug:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Debug/libglad.a:
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Debug/libglad.a


PostBuild.glfw.Debug:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/Debug/libglfw3.a:
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/Debug/libglfw3.a


PostBuild.FreeImage.Debug:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/Debug/libFreeImage.a:
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/Debug/libFreeImage.a


PostBuild.earth.Release:
PostBuild.glfw.Release: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Release/earth.app/Contents/MacOS/earth
PostBuild.glad.Release: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Release/earth.app/Contents/MacOS/earth
PostBuild.FreeImage.Release: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Release/earth.app/Contents/MacOS/earth
PostBuild.glad.Release: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Release/earth.app/Contents/MacOS/earth
PostBuild.glfw.Release: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Release/earth.app/Contents/MacOS/earth
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Release/earth.app/Contents/MacOS/earth:\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/Release/libglfw3.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Release/libglad.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/Release/libFreeImage.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Release/libglad.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/Release/libglfw3.a
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Release/earth.app/Contents/MacOS/earth


PostBuild.glad.Release:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Release/libglad.a:
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Release/libglad.a


PostBuild.glfw.Release:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/Release/libglfw3.a:
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/Release/libglfw3.a


PostBuild.FreeImage.Release:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/Release/libFreeImage.a:
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/Release/libFreeImage.a


PostBuild.earth.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/MinSizeRel/earth.app/Contents/MacOS/earth
PostBuild.glad.MinSizeRel: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/MinSizeRel/earth.app/Contents/MacOS/earth
PostBuild.FreeImage.MinSizeRel: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/MinSizeRel/earth.app/Contents/MacOS/earth
PostBuild.glad.MinSizeRel: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/MinSizeRel/earth.app/Contents/MacOS/earth
PostBuild.glfw.MinSizeRel: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/MinSizeRel/earth.app/Contents/MacOS/earth
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/MinSizeRel/earth.app/Contents/MacOS/earth:\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/MinSizeRel/libglfw3.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/MinSizeRel/libglad.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/MinSizeRel/libFreeImage.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/MinSizeRel/libglad.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/MinSizeRel/earth.app/Contents/MacOS/earth


PostBuild.glad.MinSizeRel:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/MinSizeRel/libglad.a:
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/MinSizeRel/libglad.a


PostBuild.glfw.MinSizeRel:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/MinSizeRel/libglfw3.a:
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/MinSizeRel/libglfw3.a


PostBuild.FreeImage.MinSizeRel:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/MinSizeRel/libFreeImage.a:
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/MinSizeRel/libFreeImage.a


PostBuild.earth.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/RelWithDebInfo/earth.app/Contents/MacOS/earth
PostBuild.glad.RelWithDebInfo: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/RelWithDebInfo/earth.app/Contents/MacOS/earth
PostBuild.FreeImage.RelWithDebInfo: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/RelWithDebInfo/earth.app/Contents/MacOS/earth
PostBuild.glad.RelWithDebInfo: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/RelWithDebInfo/earth.app/Contents/MacOS/earth
PostBuild.glfw.RelWithDebInfo: /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/RelWithDebInfo/earth.app/Contents/MacOS/earth
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/RelWithDebInfo/earth.app/Contents/MacOS/earth:\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/RelWithDebInfo/libglfw3.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/RelWithDebInfo/libglad.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/RelWithDebInfo/libFreeImage.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/RelWithDebInfo/libglad.a\
	/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/RelWithDebInfo/earth.app/Contents/MacOS/earth


PostBuild.glad.RelWithDebInfo:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/RelWithDebInfo/libglad.a:
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/RelWithDebInfo/libglad.a


PostBuild.glfw.RelWithDebInfo:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/RelWithDebInfo/libglfw3.a:
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/RelWithDebInfo/libglfw3.a


PostBuild.FreeImage.RelWithDebInfo:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/RelWithDebInfo/libFreeImage.a:
	/bin/rm -f /Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/RelWithDebInfo/libFreeImage.a




# For each target create a dummy ruleso the target does not have to exist
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Debug/libglad.a:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/Debug/libFreeImage.a:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/MinSizeRel/libFreeImage.a:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/RelWithDebInfo/libFreeImage.a:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/FreeImage3151/Release/libFreeImage.a:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/MinSizeRel/libglad.a:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/RelWithDebInfo/libglad.a:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/Release/libglad.a:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/Debug/libglfw3.a:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/MinSizeRel/libglfw3.a:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/RelWithDebInfo/libglfw3.a:
/Users/sambeebe/Documents/summateaching-assignment_4-ac0d2df6604a/build/glfw-3.2/src/Release/libglfw3.a:
