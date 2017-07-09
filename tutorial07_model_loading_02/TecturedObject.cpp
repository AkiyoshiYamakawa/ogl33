#include "TexturedObject.h"
#include <iostream>
using namespace std;

//int TexturedObject::init(char* vshaderFile, char* fshaderFile, char* objFile, char* ddsFile, char* strMVP0){
int TexturedObject::init(char* vshaderFile, char* fshaderFile, char* objFile, char* ddsFile){

	cout<<"TexturedObject() called"<<endl;
	//GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	//GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );
	//programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );
	programID = LoadShaders( vshaderFile, fshaderFile);

	// Get a handle for our "MVP" uniform
	//GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	//strMVP = strMVP0;
	//MatrixID = glGetUniformLocation(programID, strMVP);

	// Load the texture
	//GLuint Texture = loadDDS("uvmap.DDS");
	//Texture = loadDDS("uvmap.DDS");
	//Texture = loadDDS("sphere-plate.DDS");
	Texture = loadDDS(ddsFile);
	
	// Get a handle for our "myTextureSampler" uniform
	//GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
	TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	// Read our .obj file
	//std::vector<glm::vec3> vertices;
	//std::vector<glm::vec2> uvs;
	//std::vector<glm::vec3> normals; // Won't be used at the moment.
	//bool res = loadOBJ("cube.obj", vertices, uvs, normals);
	//bool res = loadOBJ("sphere-plate.obj", vertices, uvs, normals);
	bool res = loadOBJ( objFile, vertices, uvs, normals);
	//bool res = loadOBJ("sphere-plate-emit.obj", vertices, uvs, normals);

	// Load it into a VBO

	//GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	//GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	return 0;
}

int TexturedObject::draw(glm::mat4 MVP) {

		// Use our shader
		glUseProgram(programID);

		MatrixID = glGetUniformLocation(programID, "MVP");

	
	// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		//// Use our shader
		//glUseProgram(programID);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		return 0;

}

int TexturedObject::finalize() {
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);
	return 0;
}

