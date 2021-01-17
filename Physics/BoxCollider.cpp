#include "stdafx.h"

//Functions
bool BoxCollider::doCollideTop(Entity* self, Entity* other)
{
	if (BoxCollider::isCollideTop(self, other)) {
		self->setBottom(other->getTop());
		self->collideTop();

		return true;
	}
	return false;
}

bool BoxCollider::doCollideBottom(Entity* self, Entity* other)
{
	if (BoxCollider::isCollideBottom(self, other)) {
		self->setTop(other->getBottom());
		self->collideBottom();

		return true;
	}
	return false;
}

bool BoxCollider::doCollideRight(Entity* self, Entity* other)
{
	if (BoxCollider::isCollideRight(self, other)) {
		self->setRight(other->getLeft());
		self->collideRight();

		return true;
	}
	return false;
}

bool BoxCollider::doCollideLeft(Entity* self, Entity* other)
{
	if (BoxCollider::isCollideLeft(self, other)) {
		self->setLeft(other->getRight());
		self->collideLeft();

		return true;
	}
	return false;
}

bool BoxCollider::isCollideTop(Entity* self, Entity* other)
{
	return self->getBottom() >= other->getTop() && self->getPrevBottom() <= other->getTop();
}

bool BoxCollider::isCollideBottom(Entity* self, Entity* other)
{
	return self->getTop() <= other->getBottom() && self->getPrevTop() >= other->getBottom();
}

bool BoxCollider::isCollideRight(Entity* self, Entity* other)
{
	return self->getRight() >= other->getLeft() && self->getPrevRight() <= other->getLeft();
}

bool BoxCollider::isCollideLeft(Entity* self, Entity* other)
{
	return self->getLeft() <= other->getRight() && self->getPrevLeft() >= other->getRight();
}

const bool BoxCollider::isOverlap(Entity& self, Entity& other)
{
	if (self.getBottom() > other.getTop() &&
		self.getTop() < other.getBottom() &&
		self.getRight() > other.getLeft() &&
		self.getLeft() < other.getRight())
	{
		return true;
	}

	return false;
}

const void BoxCollider::doResponse(Entity& self, Entity& other)
{
	if (BoxCollider::doCollideTop(&self, &other))
		return;
	if (BoxCollider::doCollideLeft(&self, &other))
		return;
	if (BoxCollider::doCollideRight(&self, &other))
		return;
	if (BoxCollider::doCollideBottom(&self, &other))
		return;
}