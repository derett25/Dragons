// Protocol class used to enforce encapsulation for context containers
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_CONTEXTCONTAINER
#define INCLUDED_CONTEXTCONTAINER

class GameContext;

class ContextContainer {
public:
	virtual ~ContextContainer();
	virtual void add(GameContext* context) = 0;
	virtual void pop() = 0;
};

#endif