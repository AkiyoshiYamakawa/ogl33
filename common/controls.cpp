// Include GLFW
#include <glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ModelMatrix,RotateMatrix, TranslateMatrix;
glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}
glm::mat4 getModelMatrix(){
	return ModelMatrix;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 5 );
glm::vec3 movedist = glm::vec3( 0, 0, 0 );

// Initial horizontal angle : toward -Z
double horizontalAngle = 3.14f;
// Initial vertical angle : none
double verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;
// distance
double radius = 10.0f;
float qtangle = 0.0f;

float speed = 3.0f*0.001; // 3 units / second
float mouseSpeed = 0.005f;

vec3 up2 = vec3(0,1,0);
vec3 vn = vec3(0,0,1);
vec3 ax = vec3(0,0,0);


void computeMatricesFromInputs(){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024/2, 768/2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024/2 - xpos );
	if(horizontalAngle < glm::radians(-360.0f) ) {
		horizontalAngle += glm::radians(+360.0f) ;
	}else
	if(horizontalAngle > glm::radians(+360.0f) ) {
		horizontalAngle += glm::radians(-360.0f) ;
	}
	
	verticalAngle   += mouseSpeed * float( 768/2 - ypos );
	if(verticalAngle < glm::radians(-89.0f) ) {
		verticalAngle = glm::radians(-89.0f) ;
	}else
	if(verticalAngle > glm::radians(+89.0f) ) {
		verticalAngle = glm::radians(+89.0f) ;
	}

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
	//glm::vec3 up = glm::cross( right, direction );
	glm::vec3 up = glm::vec3(0,1,0);

	// CloseUP
	if (glfwGetKey( window, GLFW_KEY_PAGE_UP ) == GLFW_PRESS){
		//position += direction * deltaTime * speed;
		radius -= 0.005f;
		if( radius < 0 ){
			radius = 0;
		}
	}
	// Zoomout
	if (glfwGetKey( window, GLFW_KEY_PAGE_DOWN ) == GLFW_PRESS){
		//position += direction * deltaTime * speed;
		radius += 0.005;
	}
	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		//position += direction * deltaTime * speed;
		verticalAngle += 0.005;
		if( verticalAngle > glm::radians(85.0) ){
			verticalAngle = glm::radians(85.0);
		}
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		//position -= direction * deltaTime * speed;
		verticalAngle -= 0.005;
		if( verticalAngle < glm::radians(-85.0) ){
			verticalAngle = glm::radians(-85.0);
		}
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		//position += right * deltaTime * speed;
		horizontalAngle += 0.005;
		if( horizontalAngle > glm::radians(360.0) ){
			horizontalAngle -= glm::radians(360.0);
		}
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		//position -= right * deltaTime * speed;
		horizontalAngle -= 0.005;
		if( horizontalAngle < glm::radians(-360.0) ){
			horizontalAngle += glm::radians(360.0);
		}
	}
	
	// move left 'a'
	if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS) {
		movedist.x -= speed;
		//vn = -position;
		vn = vec3( -1,0,0);
		//qtangle += 0.005f;
		qtangle += speed;

	}
	// move Right 'd'
	if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS) {
		movedist.x += speed;
		vn = vec3( +1,0,0);
		//vn = position;
		//qtangle += 0.005f;
		//qt = quat( qtangle, glm::cross(vn,up2));
		qtangle += speed;
	}
	// move forward 'w'
	if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS) {
		movedist.z -= speed;
		vn = vec3( 0,0,-1);
		//vn = glm::cross(position,up2);
		//qtangle += 0.005f;
		//qt = quat( qtangle, glm::cross(vn,up2));
		qtangle += speed;
	}
	// move backward 's'
	if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS) {
		movedist.z += speed;
		vn = vec3( 0,0,+1);
		//vn = glm::cross(-position,up2);
		//qtangle += 0.005f;
		//qt = quat( qtangle, glm::cross(vn,up2));
		qtangle += speed;
	}

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.
	position.x = radius * cos(verticalAngle)*cos(horizontalAngle);
	position.y = radius * sin(verticalAngle);
	position.z = radius * cos(verticalAngle)*sin(horizontalAngle);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Model matrix
	TranslateMatrix		= glm::translate(glm::mat4(1.0f),movedist);
	//ModelMatrix     = glm::toMat4(qt);
	//qtangle += degrees(speed);
	RotateMatrix		= glm::rotate(glm::mat4(1.0f),qtangle,cross(up2,vn));
	ModelMatrix = TranslateMatrix * RotateMatrix ;
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								//position+direction, // and looks here : at the same position, plus "direction"
								vec3(0,0,0),		// and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}