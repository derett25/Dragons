// Class that represents the camera
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_CAMERA
#define INCLUDED_CAMERA

#include "Vector2D.h"

class Camera {
public:
	Camera(int scrollSpeed = 5);
	~Camera();
	void moveCamera(Vector2D& direction);
	void setPosition(int coordinate);
	Vector2D& getPosition();
private:
	int mScrollSpeed;
	Vector2D mPosition;
};

#endif