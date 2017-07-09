#ifndef _TexturedObject_H_
#define _TexturedObject_H_

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>

class TexturedObject {
public:
	//TexturedObject();
	//~TexturedObject();

private:
	GLuint VertexArrayID;
	GLuint programID;
	GLuint MatrixID;
	GLuint Texture;
	GLuint TextureID;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	GLuint vertexbuffer;
	GLuint uvbuffer;
	char*  strMVP;

public:
	//int init(char*, char*, char*, char*, char*);
	int init(char*, char*, char*, char*);
	int draw(glm::mat4);
	int finalize();

};

#endif