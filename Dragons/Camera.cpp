#include "Camera.h"
#include "CustomMouse.h"

Camera::Camera(int scrollSpeed) :
	mScrollSpeed(scrollSpeed) {
}


Camera::~Camera() {
}

void Camera::moveCamera(Vector2D& direction) {
	mPosition += (direction * mScrollSpeed);
}

void Camera::setPosition(int coordinate) {
	mPosition = coordinate;
}

Vector2D& Camera::getPosition() {
	return mPosition;
}