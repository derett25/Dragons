// Protocol class used to enforce encapsulation for entity containers
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_ENTITYCONTAINER
#define INCLUDED_ENTITYCONTAINER

class Entity;

class EntityContainer {
public:
	virtual ~EntityContainer();
	virtual void add(Entity* entity) = 0;
	virtual void remove(Entity* entity) = 0;
};

#endif