#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Core/Input.h"
#include "../Core/GameEngine.h"

class Camera
{
public:
	Camera();
	Camera(float fov, int width, int height, float zNear, float zFar);
	void Init(float fov, int width, int height, float zNear, float zFar);
	void Update();
	glm::mat4 getViewMatrix() { return viewMatrix; };
	glm::mat4 getProjectionMatrix() {return projectionMatrix;};
    glm::vec3 getCameraPosition() {return cameraPosition;};
	void SetCameraPosition(glm::vec3 position) { cameraPosition = position; }
	~Camera(void);
protected:
private:
	float moveSpeed;
	float rotationSpeed;
	glm::vec3 cameraRotation;
    glm::vec3 cameraPosition;
    glm::vec3 cameraForward;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;
    glm::vec3 forwardVector;
    glm::vec3 worldUp;
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    void UpdateCameraVectors();
};

