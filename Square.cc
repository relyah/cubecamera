#include "Square.h"

Square::Square(IOpenGLProgram* program, IModel* model, bool isRenderToFBO) :
  AbstractObject(program,model,isRenderToFBO) {
  //logger = Logger::GetLogger();

}

Square::~Square() {
  model=0;
}

void Square::Init() {

  Gen();

  attribute_vp = program->GetAttrib("vp");
  attribute_vn = program->GetAttrib("vn");
  attribute_vc = program->GetAttrib("vc");

  uniform_m = program->GetUniform("model");
  uniform_v = program->GetUniform("view");
  uniform_p = program->GetUniform("projection");

  sstm.str(std::string());
  sstm << "Square attributes vp: " << attribute_vp << ", vn: " << attribute_vn << ", vc: " << attribute_vc << ", uniform m: " << uniform_m  << ", uniform_p: " << uniform_p << std::endl;
  logger->info(sstm.str());


  FillVBO();
  InitFBO();
  Unbind();
}

void Square::FillVBO() {

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
  sstm.str(std::string());
  sstm << "Square vboPoints: " << vboPoints << std::endl;
  logger->info(sstm.str());
  glBufferData(GL_ARRAY_BUFFER, numPoints * sizeof(VertexStructure), points, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPoints);
  sstm.str(std::string());
  sstm << "Square iboPoints: " << iboPoints << std::endl;
  logger->info(sstm.str());
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,numIndices*sizeof(unsigned short), pointsIndex, GL_STATIC_DRAW);

  glEnableVertexAttribArray(attribute_vp);
  glVertexAttribPointer (attribute_vp, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (GLubyte*)NULL);

  glEnableVertexAttribArray(attribute_vn);
  glVertexAttribPointer(attribute_vn, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure),(GLvoid*)offsetof(struct VertexStructure, normal));

  glEnableVertexAttribArray(attribute_vc);
  glVertexAttribPointer(attribute_vc, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure),(GLvoid*)offsetof(struct VertexStructure, colour));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Square::InitFBO() {
  if  (!isRenderToFBO) {return;}

  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  glGenTextures(1, &color_texture);
  glBindTexture(GL_TEXTURE_2D, color_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int size = 512;
  glTexStorage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size,size);

  unsigned char* data = (unsigned char*) malloc(size * size * 4);
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
//			data[count++] = count%255;//(unsigned char) (255.0f * sin(alpha));//
//			data[count++] =count%255;//(unsigned char) (255.0f * cos(beta));//
//			data[count++] =count%255;// (unsigned char) (255.0f * sin(beta) * cos(alpha));//
//			data[count++]=255;
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

  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, color_texture, 0);
  //glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_texture, 0);

  static const GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };
  glDrawBuffers(1, draw_buffers);

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Square::Render() {
  Bind();

  if (isRenderToFBO) {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glBindTexture(GL_TEXTURE_2D, color_texture);
  }

  //logger->info("Square updating...");
  glm::mat4 modelMatrix = model->GetModel();
  glUniformMatrix4fv(uniform_m,1,GL_FALSE,glm::value_ptr(modelMatrix));

  glm::mat4 viewMatrix = model->GetView();
  glUniformMatrix4fv(uniform_v,1,GL_FALSE,glm::value_ptr(viewMatrix));

  glm::mat4 projectionMatrix = model->GetProjection();
  glUniformMatrix4fv(uniform_p,1,GL_FALSE,glm::value_ptr(projectionMatrix));

  sstm.str(std::string());
  sstm << "Square vboPoints: " << vboPoints << std::endl;
  logger->info(sstm.str());
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPoints);
  glDrawElements(GL_TRIANGLES,numIndices,GL_UNSIGNED_SHORT,0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  if (isRenderToFBO) {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  Unbind();
}

void Square::Shutdown() {
  AbstractObject::Shutdown();

  if (isRenderToFBO) {
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &color_texture);
  }

  glDeleteBuffers(1, &vboPoints);
  glDeleteBuffers(1, &iboPoints);

  program=0;
  model=0;
}

