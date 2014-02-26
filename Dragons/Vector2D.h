// Class that represents a position in the game
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_VECTOR2D
#define INCLUDED_VECTOR2D

class Vector2D {
public:
	Vector2D() :
		mX(0),
		mY(0) {
	}

	Vector2D(int x, int y) :
		mX(x),
		mY(y) {
	}

	~Vector2D() {
		mX = 0;
		mY = 0;
	}

	int getX() const {
		return mX;
	}

	int getY() const {
		return mY;
	}

	void setX(int x) {
		mX = x;
	}

	void setY(int y) {
		mY = y;
	}

	Vector2D& operator= (const Vector2D& vector)
	{
		mX = vector.getX();
		mY = vector.getY();
		return *this;
	}

	Vector2D& operator= (const int& integer)
	{
		mX = integer;
		mY = integer;
		return *this;
	}

	Vector2D& operator+= (const Vector2D& vector)
	{
		mX += vector.getX();
		mY += vector.getY();
		return *this;
	}

	Vector2D& operator+= (const int &integer)
	{
		mX += integer;
		mY += integer;
		return *this;
	}
private:
	int mX;
	int mY;
};

	/* Inline operator overloaders */

	inline Vector2D operator+ (const Vector2D& vector0, const Vector2D& vector1) {
		return Vector2D(vector0.getX() + vector1.getX(), vector0.getY() + vector1.getY());
	}

	inline Vector2D operator+ (int number, const Vector2D& vector) {
		return Vector2D(vector.getX() + number, vector.getY() + number);
	}

	inline Vector2D operator+ (const Vector2D& vector, int number) {
		return Vector2D(vector.getX() + number, vector.getY() + number);
	}

	inline Vector2D operator- (const Vector2D& vector0, const Vector2D& vector1) {
		return Vector2D(vector0.getX() - vector1.getX(), vector0.getY() - vector1.getY());
	}

	inline Vector2D operator- (const Vector2D& vector, int number) {
		return Vector2D(vector.getX() - number, vector.getY() - number);
	}

	inline Vector2D operator- (int number, const Vector2D& vector) {
		return Vector2D(vector.getX() - number, vector.getY() - number);
	}

	inline Vector2D operator* (const Vector2D& vector0, const Vector2D& vector1) {
		return Vector2D(vector0.getX() * vector1.getX(), vector0.getY() * vector1.getY());
	}

	inline Vector2D operator* (const Vector2D& vector, int number) {
		return Vector2D(vector.getX() * number, vector.getY() * number);
	}

	inline Vector2D operator* (int number, const Vector2D& vector) {
		return Vector2D(vector.getX() * number, vector.getY() * number);
	}

	inline bool operator== (const Vector2D& vector0, const Vector2D& vector1) {
		return ((vector0.getX() == vector1.getX()) && (vector0.getY() == vector1.getY()));
	}

	inline bool operator>= (const Vector2D& vector0, const Vector2D& vector1) {
		return ((vector0.getX() >= vector1.getX()) && (vector0.getY() >= vector1.getY()));
	}

	inline bool operator<= (const Vector2D& vector0, const Vector2D& vector1) {
		return ((vector0.getX() <= vector1.getX()) && (vector0.getY() <= vector1.getY()));
	}

	inline bool operator!= (const Vector2D& vector0, const Vector2D& vector1) {
		return ((vector0.getX() != vector1.getX()) || (vector0.getY() != vector1.getY()));
	}

	inline bool operator!= (const Vector2D& vector, int number) {
		return ((vector.getX() != number) || (vector.getY() != number));
	}

	inline bool operator!= (int number, const Vector2D& vector) {
		return ((vector.getX() != number) || (vector.getY() != number));
	}

#endif