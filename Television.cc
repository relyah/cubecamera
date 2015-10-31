#include "Television.h"

Television::Television(IOpenGLProgram* program, IModel* model, IObject *source) :
  AbstractObject(program,model,false), source(source) {
  //logger = Logger::GetLogger();

}

Television::~Television() {
  model=0;
}

void Television::Init() {

  Gen();

  attribute_vp = program->GetAttrib("vp");
  attribute_vt = program->GetAttrib("vt");

  uniform_m = program->GetUniform("model");
  uniform_v = program->GetUniform("view");
  uniform_p = program->GetUniform("projection");

  sstm.str(std::string());
  sstm << "TV attributes vp: " << attribute_vp << ", vt: " << attribute_vt << ", uniform m: " << uniform_m  << ", uniform_p: " << uniform_p << std::endl;
  logger->info(sstm.str());

  
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

  FillVBO();
  Unbind();
}

void Television::FillVBO() {

  numPoints = 4;
  TVStructure points[] = {
    1.0f,  0.0f,  0.1f, 1.0f,0.0f,
    1.0f, -1.0f,  0.1f, 1.0f,1.0f,
    0.0f, -1.0f, 0.1f, 0.0f,1.0f,
    0.0f, 0.0f, 0.1f, 0.0f,0.0f
  };

  numIndices = 6;
  unsigned short pointsIndex[] = {
    0,1,2,2,3,0};

  glGenBuffers(1, &vboPoints);
  glGenBuffers(1, &iboPoints);

  glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
  sstm.str(std::string());
  sstm << "TV vboPoints: " << vboPoints << std::endl;
  logger->info(sstm.str());
  glBufferData(GL_ARRAY_BUFFER, numPoints * sizeof(VertexStructure), points, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPoints);
  sstm.str(std::string());
  sstm << "TV iboPoints: " << iboPoints << std::endl;
  logger->info(sstm.str());
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,numIndices*sizeof(unsigned short), pointsIndex, GL_STATIC_DRAW);

  glEnableVertexAttribArray(attribute_vp);
  glVertexAttribPointer (attribute_vp, 3, GL_FLOAT, GL_FALSE, sizeof(TVStructure), (GLubyte*)NULL);

  glEnableVertexAttribArray(attribute_vt);
  glVertexAttribPointer(attribute_vt, 2, GL_FLOAT, GL_FALSE, sizeof(TVStructure),(GLvoid*)offsetof(struct TVStructure, texcoord));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Television::Render() {

  Bind();
  glBindFramebuffer(GL_FRAMEBUFFER,0);

  //logger->info("TV updating...");
  glm::mat4 modelMatrix = model->GetModel();
  glUniformMatrix4fv(uniform_m,1,GL_FALSE,glm::value_ptr(modelMatrix));

  glm::mat4 viewMatrix = model->GetView();
  glUniformMatrix4fv(uniform_v,1,GL_FALSE,glm::value_ptr(viewMatrix));

  glm::mat4 projectionMatrix = model->GetProjection();
  glUniformMatrix4fv(uniform_p,1,GL_FALSE,glm::value_ptr(projectionMatrix));

  sstm.str(std::string());
  sstm << "TV vboPoints: " << vboPoints << std::endl;
  logger->info(sstm.str());

  //glActiveTexture(GL_TEXTURE0);
  //glBindTexture(GL_TEXTURE_2D,color_texture);//
/*
  std::cout << "using color_texture=" <<source->GetColorTexture() << std::endl;
  //glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,  source->GetColorTexture()); //color_texture);//

  int size = 512;
  unsigned char* dataTEX = (unsigned char*) malloc(size * size * 4);
  glGetTexImage(GL_TEXTURE_2D,0,GL_RGBA,GL_UNSIGNED_BYTE,dataTEX);

	for (int col = 0; col < size; col++) {
		float alpha = (float) M_PI * col * 360.0f / ((float) size * 180.0f);
		for (int row = 0; row < size; row++) {
			float beta = (float) M_PI * row * 360.0f / ((float) size * 180.0f);
			//std::cout << (col * size + row)*4 << " " << count << std::endl;
			int index = (col * size + row) * 4;
			dataTEX[index] = (unsigned char) (255.0f * sin(alpha));
			dataTEX[index + 1] = (unsigned char) (255.0f * cos(beta));
			dataTEX[index + 2] = (unsigned char) (255.0f * sin(beta) * cos(alpha));
			dataTEX[index + 3] = 255;
    }
  }
*/
  /*for (int col = 0; col < size; col++) {
    for (int row = 0; row < size; row++) {
    int index = (col * size + row) * 4;
    //if (dataFBO[index]!=dataTEX[index]) {std::cout << "ERROR" << std::endl;}
    //std::cout << (int)(dataTEX[index]) << " ";
    }
    //std::cout << std::endl;
    }*/

  /*
  glTexImage2D(GL_TEXTURE_2D, // target
               0,  // level, 0 = base, no minimap,
               GL_RGBA, // internalformat
               size,  // width
               size,  // height
               0,  // border, always 0 in OpenGL ES
               GL_RGBA,  // format
               GL_UNSIGNED_BYTE, // type
               dataTEX);

  free(dataTEX);
*/
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPoints);
  glDrawElements(GL_TRIANGLES,numIndices,GL_UNSIGNED_SHORT,0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  //glBindTexture(GL_TEXTURE_2D, 0);

  Unbind();
}

void Television::Shutdown() {
  AbstractObject::Shutdown();

  glDeleteBuffers(1, &vboPoints);
  glDeleteBuffers(1, &iboPoints);

  program=0;
  model=0;
  source=0;
}

