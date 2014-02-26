// Tool class used to simplify the creation of entities and to remove physical compilation dependencies
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_ENTITYTOOL
#define INCLUDED_ENTITYTOOL

class Entity;
class Vector2D;

struct EntityTool {
	static Entity* createDragon(Vector2D& vector);
	static Entity* createFood(Vector2D& vector);
	static Entity* createEgg(Vector2D& vector);
};

#endif
