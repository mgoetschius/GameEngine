#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(float fov, int width, int height, float zNear, float zFar)
{
	projectionMatrix = glm::perspective(fov, (float)width/(float)height, zNear, zFar);
	cameraRotation = glm::vec3(0.0);
	cameraPosition = glm::vec3(0.0, 1.0, 3.0);
	worldUp = glm::vec3(0.0, 1.0, 0.0);
	UpdateCameraVectors();
	viewMatrix = glm::lookAt(cameraPosition, cameraPosition-cameraForward, worldUp); 

	moveSpeed = .005f;
    rotationSpeed = 0.05f;
}

void Camera::Init(float fov, int width, int height, float zNear, float zFar)
{
	projectionMatrix = glm::perspective(fov, (float)width/(float)height, zNear, zFar);
	cameraRotation = glm::vec3(0.0);
	cameraPosition = glm::vec3(0.0, 1.0, 3.0);
	worldUp = glm::vec3(0.0, 1.0, 0.0);
	UpdateCameraVectors();
	viewMatrix = glm::lookAt(cameraPosition, cameraPosition-cameraForward, worldUp); 

	moveSpeed = .2f;
    rotationSpeed = 2.0f;
}

void Camera::Update()
{
	if(Input::keys[Input::KEY_W])
    {
        cameraPosition -= moveSpeed * forwardVector;
        UpdateCameraVectors();
    }
    if(Input::keys[Input::KEY_S])
    {
        cameraPosition += moveSpeed * forwardVector;
        UpdateCameraVectors();
    }
	if(Input::keys[Input::KEY_A])
    {
        cameraRotation.y += rotationSpeed;
        UpdateCameraVectors();
    }
    if(Input::keys[Input::KEY_D])
    {
        cameraRotation.y -= rotationSpeed;
        UpdateCameraVectors();
    }
	if(Input::keys[Input::KEY_E])
	{
		cameraPosition.y += .1;
	}
	if(Input::keys[Input::KEY_C] && cameraPosition.y > 1.0)
	{
		cameraPosition.y -= .1;
	}

	viewMatrix = glm::lookAt(cameraPosition, cameraPosition-cameraForward, worldUp);
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 front;
    front.z = cos(glm::radians(cameraRotation.x)) * cos(glm::radians(cameraRotation.y));
    front.y = sin(glm::radians(cameraRotation.x));
    front.x = cos(glm::radians(cameraRotation.x)) * sin(glm::radians(cameraRotation.y));
    cameraForward = glm::normalize(front);
    cameraRight = glm::normalize(glm::cross(cameraForward, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraForward, cameraRight));
    forwardVector = glm::normalize(glm::vec3(front.x, 0.0f, front.z));
}


Camera::~Camera(void)
{
}
