#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#define GLM_MESSAGES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

struct VertexStructure {
	float coord3d[3];
	float normal[3];
	float colour[3];
};

struct TVStructure {
  float coord3d[3];
  float texcoord[2];
};

int screenWidth=640;
int screenHeight=480;
GLuint vao;
GLuint vboPoints;
GLuint iboPoints;
GLuint attribute_vp, attribute_vn, attribute_vc;
GLint uniform_m;
GLint uniform_v;
GLint uniform_p;
int numPoints, numIndices;

GLuint fboTV;
GLuint vaoTV;
GLuint vboPointsTV;
GLuint iboPointsTV;
GLuint attribute_vpTV, attribute_vtTV;
GLint uniform_mTV;
GLint uniform_vTV;
GLint uniform_pTV;
int numPointsTV, numIndicesTV;
GLuint color_textureTV;

GLuint CreateProgram(const char *vertexfile, const char *fragmentfile, GLuint &vshader, GLuint &fshader);
GLuint CreateShader(GLenum type, const char *filename);
void print_log(GLuint object);
char* file_read(const char* filename);
GLint GetUniform(GLuint program, const char *name);
GLint GetAttrib(GLuint program, const char *name);

int main() {

  //------------------------------------------------------------------
  glfwInit();
  GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Cube", NULL, NULL);
  glfwMakeContextCurrent(window);
  glewInit();
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  //glDepthFunc(GL_LESS);
  //glEnable(GL_CULL_FACE); // cull face
  //glCullFace(GL_BACK); // cull back face
  //glFrontFace(GL_CCW); // GL_CCW for counter clock-wise //GL_CW
  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glPolygonMode(GL_FRONT, GL_LINE); //for wireframe
  //glPolygonMode(GL_BACK, GL_LINE); //for wireframe
  glClear(GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
  //------------------------------------------------------------------

  //------------------------------------------------------------------
	const char *vertexfile="cube.vs.glsl";
  const char *fragmentfile="cube.fs.glsl";
  GLuint vshader;
	GLuint fshader;
  GLuint program = CreateProgram(vertexfile, fragmentfile, vshader, fshader);
  //------------------------------------------------------------------

  //------------------------------------------------------------------
	const char *vertexfileTV="tvvs.glsl";
  const char *fragmentfileTV="tvfs.glsl";
  GLuint vshaderTV;
	GLuint fshaderTV;
  GLuint programTV = CreateProgram(vertexfileTV, fragmentfileTV, vshaderTV, fshaderTV);
  //------------------------------------------------------------------

  //------------------------------------------------------------------
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  attribute_vp = GetAttrib(program,"vp");
  attribute_vn = GetAttrib(program,"vn");
  attribute_vc = GetAttrib(program,"vc");

  uniform_m = GetUniform(program,"model");
  uniform_v = GetUniform(program,"view");
  uniform_p = GetUniform(program,"projection");


  numPoints = 4;
  VertexStructure points[] = {
  0.5f,  0.5f,  0.5f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f,
    0.5f, -0.5f,  0.5f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f,

    0.5f,  0.5f,  -0.5f, 0.0f,0.0f,-1.0f, 0.0f,1.0f,0.0f,
    0.5f, -0.5f,  -0.5f, 0.0f,0.0f,-1.0f, 0.0f,1.0f,0.0f,
    -0.5f, -0.5f,  -0.5f, 0.0f,0.0f,-1.0f, 0.0f,1.0f,0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f,0.0f,-1.0f, 0.0f,1.0f,0.0f,

    -0.5f, -0.5f, 0.5f, -1.0f,0.0f,0.0f, 1.0f,0.0f,0.0f,
    -0.5f, -0.5f,  -0.5f, -1.0f,0.0f,-1.0f, 0.0f,1.0f,0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f,0.0f,0.0f, 1.0f,0.0f,0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f,0.0f,0.0f, 0.0f,1.0f,0.0f

    };

  numIndices = 6;
  unsigned short pointsIndex[] = {
  0,1,2,2,3,0,
    4,6,5,6,4,7,
    8,9,10,10,9,11};

  glGenBuffers(1, &vboPoints);
  glGenBuffers(1, &iboPoints);

  glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
  glBufferData(GL_ARRAY_BUFFER, numPoints * sizeof(VertexStructure), points, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPoints);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,numIndices*sizeof(unsigned short), pointsIndex, GL_STATIC_DRAW);

  glEnableVertexAttribArray(attribute_vp);
  glVertexAttribPointer (attribute_vp, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (GLubyte*)NULL);

  glEnableVertexAttribArray(attribute_vn);
  glVertexAttribPointer(attribute_vn, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure),(GLvoid*)offsetof(struct VertexStructure, normal));

  glEnableVertexAttribArray(attribute_vc);
  glVertexAttribPointer(attribute_vc, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure),(GLvoid*)offsetof(struct VertexStructure, colour));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
  //------------------------------------------------------------------

  //------------------------------------------------------------------

  glGenFramebuffers(1, &fboTV);
  glBindFramebuffer(GL_FRAMEBUFFER, fboTV);
  cout << "fboTV: "<<fboTV <<endl;
  //glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &color_textureTV);
  cout << "color_texture: "<<color_textureTV <<endl;
  glBindTexture(GL_TEXTURE_2D, color_textureTV);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int size = 512;
  glTexStorage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size,size);

  unsigned char* data = (unsigned char*) malloc(size * size * 4);
	for (int col = 0; col < size; col++) {
  float alpha = (float) M_PI * col * 360.0f / ((float) size * 180.0f);
  for (int row = 0; row < size; row++) {
  float beta = (float) M_PI * row * 360.0f / ((float) size * 180.0f);
  int index = (col * size + row) * 4;
  data[index] = (unsigned char) (255.0f * sin(alpha));
  data[index + 1] = (unsigned char) (255.0f * cos(beta));
  data[index + 2] = (unsigned char) (255.0f * sin(beta) * cos(alpha));
  data[index + 3] = 255;
}
}
	glTexImage2D(GL_TEXTURE_2D, // target
    0,  // level, 0 = base, no minimap,
    GL_RGBA, // internalformat
    size,  // width
    size,  // height
    0,  // border, always 0 in OpenGL ES
    GL_RGBA,  // format
    GL_UNSIGNED_BYTE, // type
    data);
	free(data);
  //glGenTextures(1, &depth_texture);
  //glBindTexture(GL_TEXTURE_2D, depth_texture);
  //glTexStorage2D(GL_TEXTURE_2D, 9, GL_DEPTH_COMPONENT32F, 512, 512);

  //glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, color_textureTV, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_textureTV, 0);
  //glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_textureTV, 0);

  static const GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };
  glDrawBuffers(1, draw_buffers);

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  //------------------------------------------------------------------


  //------------------------------------------------------------------
  glGenVertexArrays(1, &vaoTV);
  glBindVertexArray(vaoTV);

  attribute_vpTV = GetAttrib(programTV, "vp");
  attribute_vtTV = GetAttrib(programTV,"vt");

  uniform_mTV = GetUniform(programTV,"model");
  uniform_vTV = GetUniform(programTV,"view");
  uniform_pTV = GetUniform(programTV,"projection");
  
  /*glGenTextures(1, &color_textureTV);
    glBindTexture(GL_TEXTURE_2D, color_textureTV);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    size = 512;
    glTexStorage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size,size);

    data = (unsigned char*) malloc(size * size * 4);
    for (int col = 0; col < size; col++) {
    float alpha = (float) M_PI * col * 360.0f / ((float) size * 180.0f);
    for (int row = 0; row < size; row++) {
    float beta = (float) M_PI * row * 360.0f / ((float) size * 180.0f);
    //std::cout << (col * size + row)*4 << " " << count << std::endl;
    int index = (col * size + row) * 4;
    data[index] = (unsigned char) (255.0f * sin(alpha));
    data[index + 1] = (unsigned char) (255.0f * cos(beta));
    data[index + 2] = (unsigned char) (255.0f * sin(beta) * cos(alpha));
    data[index + 3] = 255;
    }
    }

    glTexImage2D(GL_TEXTURE_2D, // target
    0,  // level, 0 = base, no minimap,
    GL_RGBA, // internalformat
    size,  // width
    size,  // height
    0,  // border, always 0 in OpenGL ES
    GL_RGBA,  // format
    GL_UNSIGNED_BYTE, // type
    data);

    free(data);
  */

  numPointsTV = 4;
  TVStructure pointsTV[] = {
  1.0f,  0.0f,  0.1f, 1.0f,0.0f,
    1.0f, -1.0f,  0.1f, 1.0f,1.0f,
    0.0f, -1.0f, 0.1f, 0.0f,1.0f,
    0.0f, 0.0f, 0.1f, 0.0f,0.0f
    };

  numIndicesTV = 6;
  unsigned short pointsIndexTV[] = {
  0,1,2,2,3,0};

  glGenBuffers(1, &vboPointsTV);
  glGenBuffers(1, &iboPointsTV);

  glBindBuffer(GL_ARRAY_BUFFER, vboPointsTV);
  glBufferData(GL_ARRAY_BUFFER, numPointsTV * sizeof(VertexStructure), pointsTV, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPointsTV);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,numIndicesTV*sizeof(unsigned short), pointsIndexTV, GL_STATIC_DRAW);

  glEnableVertexAttribArray(attribute_vpTV);
  glVertexAttribPointer (attribute_vpTV, 3, GL_FLOAT, GL_FALSE, sizeof(TVStructure), (GLubyte*)NULL);

  glEnableVertexAttribArray(attribute_vtTV);
  glVertexAttribPointer(attribute_vtTV, 2, GL_FLOAT, GL_FALSE, sizeof(TVStructure),(GLvoid*)offsetof(struct TVStructure, texcoord));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindTexture(GL_TEXTURE_2D, color_textureTV);

  glBindVertexArray(0);
  //------------------------------------------------------------------

  //------------------------------------------------------------------
  glUseProgram(program);
  glBindVertexArray(vao);
  glBindFramebuffer(GL_FRAMEBUFFER, fboTV);

  //logger->info("Square updating...");
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  glUniformMatrix4fv(uniform_m,1,GL_FALSE,glm::value_ptr(modelMatrix));

  glm::mat4 viewMatrix = glm::mat4(1.0f);
  glUniformMatrix4fv(uniform_v,1,GL_FALSE,glm::value_ptr(viewMatrix));

  glm::mat4 projectionMatrix = glm::mat4(1.0f);
  glUniformMatrix4fv(uniform_p,1,GL_FALSE,glm::value_ptr(projectionMatrix));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPoints);
  glDrawElements(GL_TRIANGLES,numIndices,GL_UNSIGNED_SHORT,0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
  //------------------------------------------------------------------

  //------------------------------------------------------------------
  glUseProgram(programTV);
  glBindVertexArray(vaoTV);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  modelMatrix = glm::mat4(1.0f);
  glUniformMatrix4fv(uniform_mTV,1,GL_FALSE,glm::value_ptr(modelMatrix));

  viewMatrix = glm::mat4(1.0f);
  glUniformMatrix4fv(uniform_vTV,1,GL_FALSE,glm::value_ptr(viewMatrix));

  projectionMatrix = glm::mat4(1.0f);
  glUniformMatrix4fv(uniform_pTV,1,GL_FALSE,glm::value_ptr(projectionMatrix));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPointsTV);
  glDrawElements(GL_TRIANGLES,numIndices,GL_UNSIGNED_SHORT,0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
  //------------------------------------------------------------------

  //------------------------------------------------------------------
  glfwSwapBuffers(window);
  //------------------------------------------------------------------

  getchar();

  //------------------------------------------------------------------
  glDeleteProgram(program);
  glDeleteProgram(programTV);
  glfwTerminate();
  //------------------------------------------------------------------
}

  GLuint CreateShader(GLenum type, const char *filename) {
  GLuint s = glCreateShader(type);
  char* src = file_read(filename);
  //logger->info(src);
  glShaderSource(s, 1, &src, NULL);
  glCompileShader(s);
  GLint compile_ok = GL_FALSE;
  glGetShaderiv(s, GL_COMPILE_STATUS, &compile_ok);
  if (compile_ok == GL_FALSE) {
  cout << filename << endl;
  //fprintf(stderr, "%s:", filename);
  print_log(s);
  glDeleteShader(s);
  return 0;
}
  return s;
}

  void print_log(GLuint object) {
	GLint log_length = 0;
	if (glIsShader(object)) {
  glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
} else if (glIsProgram(object)) {
  glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
} else {
  cout << "printlog: Not a shader or a program" << endl;
  return;
}

  char* log = (char*) malloc(log_length);

  if (glIsShader(object)) {
  glGetShaderInfoLog(object, log_length, NULL, log);
} else if (glIsProgram(object)) {
  glGetProgramInfoLog(object, log_length, NULL, log);
}

  cout << log << endl;
  free(log);
}

  char* file_read(const char* filename) {

	FILE* in = fopen(filename, "rb");
	if (in == NULL)
		return NULL;
	int res_size = BUFSIZ;
	char* res = (char*) malloc(res_size);
	int nb_read_total = 0;
	while (!feof(in) && !ferror(in)) {
  if (nb_read_total + BUFSIZ > res_size) {
  if (res_size > 10 * 1024 * 1024) {
  break;
}
  res_size = res_size * 2;
  res = (char*) realloc(res, res_size);
}
  char* p_res = res + nb_read_total;
  nb_read_total += fread(p_res, 1, BUFSIZ, in);
}
	fclose(in);
	res = (char*) realloc(res, nb_read_total + 1);
	res[nb_read_total] = '\0';
	return res;

}

  GLuint CreateProgram(const char *vertexfile, const char *fragmentfile, GLuint &vshader, GLuint &fshader) {
	GLuint program = glCreateProgram();

  if (vertexfile) {
  vshader = CreateShader(GL_VERTEX_SHADER,vertexfile);
  if (!vshader)
    return 0;
  glAttachShader(program, vshader);
}
	if (fragmentfile) {
  fshader = CreateShader(GL_FRAGMENT_SHADER,fragmentfile);
  if (!fshader)
    return 0;
  glAttachShader(program, fshader);
}
	glLinkProgram(program);
	GLint link_ok = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
  cout << "glLinkProgram:" << endl;
  print_log(program);
  glDeleteProgram(program);
  return 0;
}

  return program;
}

  GLint GetAttrib(GLuint program, const char *name) {
	GLint attribute = glGetAttribLocation(program, name);
	if (attribute == -1)
		fprintf(stderr, "Could not bind attribute %s\n", name);
	return attribute;
}

  GLint GetUniform(GLuint program, const char *name) {
	GLint uniform = glGetUniformLocation(program, name);
	if (uniform == -1)
		fprintf(stderr, "Could not bind uniform %s\n", name);
	return uniform;
}
