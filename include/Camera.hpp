#pragma once

#include <glm.hpp>
#include <matrix_transform.hpp>

class   Camera
{
	private:
		glm::vec3   _position;
		glm::vec3   _front;
		glm::vec3   _right;
		glm::vec3   _worldUp;
		glm::vec3   _target;
		glm::vec3   Up;
		float       _pitch;
		float       _yaw;
		glm::mat4   _viewMatrix;
		void        _updateCamera();
	public:
		Camera();
		Camera(const Camera & rhs);
		Camera&     operator=(const Camera& rhs);
		~Camera() = default;
		void	reset();

		glm::mat4       getViewMatrix() const;
		glm::vec3       getCameraPosition();
		void            moveLeft(float val);
		void            moveRight(float val);
		void            moveUp(float val);
		void            moveDown(float val);
		void            moveForward(float val);
		void            moveBackward(float val);
		void            changeCameraXPos(float x);
		void            changeCameraYPos(float y);
		void            changeCameraZPos(float z);
		void            setCameraPosition(glm::vec3 pos);
		void            setCameraTarget(glm::vec3 target);
		void            setCameraUp(glm::vec3 up);
		glm::vec3		getPosition() const;
};
