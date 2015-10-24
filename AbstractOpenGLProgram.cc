#include "AbstractOpenGLProgram.h"

void AbstractOpenGLProgram::Use() {
  glUseProgram(this->program);
}

/*void AbstractOpenGLProgram::GenVAO() {
  if (vao==0) {
    glGenVertexArrays(1, &vao);
  }
  glBindVertexArray(vao);

  //sstm.str(std::string());
  //sstm << "vao: " << vao << std::endl;
  //logger->info(sstm.str());
  }*/

void AbstractOpenGLProgram::Shutdown() {
  glDeleteProgram(program);
  //glDeleteVertexArrays(1,&vao);
}

GLuint AbstractOpenGLProgram::CreateProgram(const char *vertexfile, const char *fragmentfile, GLuint &vshader, GLuint &fshader) {
	this->program = glCreateProgram();
	//GLuint vshader;
	if (vertexfile) {
		vshader = CreateShader(GL_VERTEX_SHADER,vertexfile);
		if (!vshader)
			return 0;
		glAttachShader(program, vshader);
	}
	//GLuint fshader;
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
    logger->error("glLinkProgram:");
		//fprintf(stderr, "glLinkProgram:");
		print_log(program);
		glDeleteProgram(program);
		return 0;
	}
  return this->program;
}

GLuint AbstractOpenGLProgram::CreateShader(GLenum type, const char *filename) {
  GLuint s = glCreateShader(type);
  char* src = file_read(filename);
  //logger->info(src);
  glShaderSource(s, 1, &src, NULL);
  glCompileShader(s);
  GLint compile_ok = GL_FALSE;
	glGetShaderiv(s, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == GL_FALSE) {
    logger->error(filename);
		//fprintf(stderr, "%s:", filename);
		print_log(s);
		glDeleteShader(s);
		return 0;
	}
  return s;
}

GLint AbstractOpenGLProgram::GetAttrib(const char *name) {
  return GetAttrib(this->program, name);
}

GLint AbstractOpenGLProgram::GetUniform(const char *name) {
  return GetUniform(this->program, name);
}

GLint AbstractOpenGLProgram::GetAttrib(GLuint program, const char *name) {
	GLint attribute = glGetAttribLocation(program, name);
	if (attribute == -1)
		fprintf(stderr, "Could not bind attribute %s\n", name);
	return attribute;
}

GLint AbstractOpenGLProgram::GetUniform(GLuint program, const char *name) {
	GLint uniform = glGetUniformLocation(program, name);
	if (uniform == -1)
		fprintf(stderr, "Could not bind uniform %s\n", name);
	return uniform;
}

char* AbstractOpenGLProgram::file_read(const char* filename) {

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

void AbstractOpenGLProgram::print_log(GLuint object) {
	GLint log_length = 0;
	if (glIsShader(object)) {
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
	} else if (glIsProgram(object)) {
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
	} else {
    logger->error("printlog: Not a shader or a program");
		//fprintf(stderr, "printlog: Not a shader or a program\n");
		return;
	}

  char* log = (char*) malloc(log_length);

  if (glIsShader(object)) {
		glGetShaderInfoLog(object, log_length, NULL, log);
	} else if (glIsProgram(object)) {
		glGetProgramInfoLog(object, log_length, NULL, log);
  }

  logger->error(log);
  //fprintf(stderr, "%s", log);
  free(log);
}

