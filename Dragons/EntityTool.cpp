#include "EntityTool.h"
#include "Vector2D.h"
#include "Dragon.h"
#include "Egg.h"
#include "Entity.h"
#include "Food.h"

Entity* EntityTool::createDragon(Vector2D& vector) {
	return new Entity(new Dragon(vector));
}

Entity* EntityTool::createFood(Vector2D& vector) {
	return new Entity(new Food(vector));
}

Entity* EntityTool::createEgg(Vector2D& vector) {
	return new Entity(new Egg(vector));
}
