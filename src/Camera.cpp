#include <Camera.hpp>

Camera::Camera(glm::vec3 position, float pitch, float yaw)
{
	_position = position;
	_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	_yaw = yaw;
	_pitch = pitch;
	_updateCamera();
}

Camera::Camera(const Camera &rhs) { *this = rhs; }

Camera& Camera::operator=(const Camera &rhs)
{
	this->_position = rhs.getPosition();
	return *this;
}

void	Camera::reset(glm::vec3 position, float pitch, float yaw) {
	_position = position;
	_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	_yaw = yaw;
	_pitch = pitch;
	_updateCamera();
}

void Camera::_updateCamera()
{
	/// Calculate the new Front vector
	glm::vec3 front;
	front.x = (float)(cos(glm::radians(_yaw)) * cos(glm::radians(_pitch)));
	front.y = (float)sin(glm::radians(_pitch));
	front.z = (float)(sin(glm::radians(_yaw)) * cos(glm::radians(_pitch)));
	_front = glm::normalize(front);
	/// Also re-calculate the Right and Up vector
	_right = glm::normalize(glm::cross(_front, _worldUp));
	Up = glm::normalize(glm::cross(_right, _front));
	_target = _position + _front;
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(_position, _target, Up);
}

void Camera::moveLeft(float val)
{
	_position -= _right * (val);
	_updateCamera();
}

void Camera::moveRight(float val)
{
	_position += _right * (val);
	_updateCamera();
}

void Camera::moveForward(float val)
{
	_position += _front * (val);
	_updateCamera();
}

void Camera::moveBackward(float val)
{
	_position -= _front * (val);
	_updateCamera();
}

void Camera::changeCameraXPos(float x)
{
	_position.x += x;
	_updateCamera();
}

void Camera::changeCameraYPos(float y)
{
	_position.y += y;
	_updateCamera();
}

void Camera::changeCameraZPos(float z)
{
	_position.z += z;
	_updateCamera();
}

glm::vec3 Camera::getCameraPosition() { return _position; }
void Camera::setCameraPosition(glm::vec3 pos) { _position = pos; }
void Camera::setCameraTarget(glm::vec3 target) { _target = target; }
void Camera::setCameraUp(glm::vec3 up) { Up = up; }
glm::vec3		Camera::getPosition() const {
	return this->_position;
}

