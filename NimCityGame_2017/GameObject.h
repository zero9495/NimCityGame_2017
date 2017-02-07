#pragma once
#include "Header.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

protected:
	BOOL GameObject::IsOnRect(POINT &coordDown);
	void GameObject::DrawRectangle(HDC &hdc);

	POINT start_;
	POINT* size_;
};

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

BOOL GameObject::IsOnRect(POINT &coordDown)
{
	return (start_.x < coordDown.x) && (coordDown.x < start_.x + size_->x) &&
		(start_.y < coordDown.y) && (coordDown.y < start_.y + size_->y);
}

void GameObject::DrawRectangle(HDC &hdc)
{
	Rectangle(hdc,
		start_.x,
		start_.y,
		start_.x + size_->x,
		start_.y + size_->y);
}