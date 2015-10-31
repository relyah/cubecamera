LIBS_GL=-lglfw -lGLEW -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread
LIBS_OTHER=-llog4cpp

IMPL_CFLAGS = -std=c++11 -D_XOPEN_SOURCE=600 \
		-D_DEFAULT_SOURCE \
		-pipe \
		-g \
		-pedantic \
		-Wall \
		-W \
		-Wmissing-prototypes \
		-Wno-sign-compare \
		-Wno-unused-parameter

CFLAGS = ${IMPL_CFLAGS}
#
## IMPL_CFLAGS = -std=c++11 -D_XOPEN_SOURCE=600 \
#		-D_DEFAULT_SOURCE \
#		-pipe \
#		-g \
#		-pedantic \
#		-Wall \
#		-W \
#		-Wno-sign-compare \
#		-Wno-unused-parameter
#
#LIBS = -lGL -lepoxy -llog4cpp
#
#CFLAGS = `pkg-config --libs --cflags gtk+-3.0` ${IMPL_CFLAGS} ${LIBS} 
#
onemain: onemain.o
	g++ ${CFLAGS} -o onemain onemain.o ${LIBS_GL}

onemain.o: onemain.cc
	g++ onemain.cc ${CFLAGS} -c

cubecamera: cubecamera.o Logger.o AdminBase.o OpenGLApplication.o OpenGLManager.o OpenGLProgram.o AbstractOpenGLProgram.o Square.o Television.o Camera.o SquareModel.o InputManager.o AbstractObject.o CrossHair.o AbstractCamera.o interface.ui.xml
	g++ ${CFLAGS} -o cubecamera cubecamera.o Logger.o AdminBase.o OpenGLApplication.o OpenGLManager.o OpenGLProgram.o AbstractOpenGLProgram.o Square.o Television.o Camera.o SquareModel.o InputManager.o AbstractObject.o CrossHair.o AbstractCamera.o

cubecamera.o: cubecamera.cc
	g++ cubecamera.cc ${CFLAGS} -c

OpenGLApplication.o: OpenGLApplication.cc OpenGLApplication.h SquareModel.o IKeyReleasedListener.h
	g++ OpenGLApplication.cc ${CFLAGS} -c

OpenGLProgram.o: OpenGLProgram.cc OpenGLProgram.h IOpenGLProgram.h IObject.h
	g++ OpenGLProgram.cc ${CFLAGS} -c

OpenGLManager.o: OpenGLManager.cc OpenGLManager.h
	g++ OpenGLManager.cc ${CFLAGS} -c

CrossHair.o: CrossHair.cc CrossHair.h
	g++ CrossHair.cc ${CFLAGS} -c

Television.o: Television.cc Television.h IObject.h AbstractObject.h DataStructures.h
	g++ Television.cc ${CFLAGS} -c

Square.o: Square.cc Square.h IObject.h AbstractObject.o IModel.h IHitable.h DataStructures.h
	g++ Square.cc ${CFLAGS} -c

SquareModel.o: SquareModel.cc SquareModel.h IModel.h IKeyReleasedListener.h
	g++ SquareModel.cc ${CFLAGS} -c

Camera.o: Camera.cc Camera.h IOpenGLProgram.h IScrollListener.h
	g++ Camera.cc ${CFLAGS} -c

AbstractCamera.o: AbstractCamera.cc AbstractCamera.h ICamera.h
	g++ AbstractCamera.cc ${CFLAGS} -c

AbstractObject.o: AbstractObject.cc AbstractObject.h
	g++ AbstractObject.cc ${CFLAGS} -c

AbstractOpenGLProgram.o: AbstractOpenGLProgram.cc AbstractOpenGLProgram.h IOpenGLProgram.h
	g++ AbstractOpenGLProgram.cc ${CFLAGS} -c

AdminBase.o: AdminBase.cc AdminBase.h
	g++ AdminBase.cc ${CFLAGS} -c

InputManager.o: InputManager.cc InputManager.h
	g++ InputManager.cc ${CFLAGS} -c

Logger.o: Logger.h Logger.cpp
	g++ Logger.cpp ${CFLAGS} -c

clean:
	rm -f cubecamera cubecamera.o *.o *.*~
