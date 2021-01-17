#pragma once

class Entity;

class BoxCollider
{
private:
	//static functions
	static bool doCollideTop(Entity* self, Entity* other);
	static bool doCollideBottom(Entity* self, Entity* other);
	static bool doCollideRight(Entity* self, Entity* other);
	static bool doCollideLeft(Entity* self, Entity* other);

public:
	//Static functions
	static bool isCollideTop(Entity* self, Entity* other);
	static bool isCollideBottom(Entity* self, Entity* other);
	static bool isCollideRight(Entity* self, Entity* other);
	static bool isCollideLeft(Entity* self, Entity* other);

	static const bool isOverlap(Entity& self, Entity& other);
	static const void doResponse(Entity& self, Entity& other);
};