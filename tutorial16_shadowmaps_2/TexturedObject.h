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
GLuint depthProgramID;
GLuint depthMatrixID;
GLuint Texture;
std::vector<glm::vec3> vertices;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals;

std::vector<unsigned short> indices;
std::vector<glm::vec3> indexed_vertices;
std::vector<glm::vec2> indexed_uvs;
std::vector<glm::vec3> indexed_normals;
GLuint vertexbuffer;
GLuint uvbuffer;
GLuint normalbuffer;
GLuint elementbuffer;
GLuint FramebufferName;
GLuint depthTexture;
// The quad's FBO. Used only for visualizing the shadowmap.
//static const GLfloat g_quad_vertex_buffer_data[18];
//static const GLfloat g_quad_vertex_buffer_data[18];
GLuint quad_vertexbuffer;
// Create and compile our GLSL program from the shaders
GLuint quad_programID ;
GLuint texID;

// Create and compile our GLSL program from the shaders
GLuint programID ;

// Get a handle for our "myTextureSampler" uniform
GLuint TextureID ;

// Get a handle for our "MVP" uniform
GLuint MatrixID ;
GLuint ViewMatrixID ;
GLuint ModelMatrixID ;
GLuint DepthBiasID ;
GLuint ShadowMapID ;

GLuint lightInvDirID ;

public:
//int init(char*, char*, char*, char*, char*);
int init(char*, char*, char*, char*,char*, char*, char*, char*);
int TexturedObject::draw1(
			glm::mat4 MVP,
			glm::mat4 ModelMatrix,
			glm::mat4 ViewMatrix
			//glm::mat4 depthBiasMVP,
			//glm::vec3 lightInvDir
		 );
/*
int TexturedObject::draw2(
			int WindowWidth, 
			int WindowHeight, 
			glm::mat4 depthMVP,
			glm::mat4 MVP,
			glm::mat4 ModelMatrix,
			glm::mat4 ViewMatrix,
			glm::mat4 depthBiasMVP,
			glm::vec3 lightInvDir
		 );
*/

int finalize();

};

#endif