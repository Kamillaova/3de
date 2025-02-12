#pragma once
#include "3Dev.h"
class Camera {
public:
	float x, y, z, speed;
	float angleX = 0, angleY = 0;

	Camera(float x, float y, float z, float speed);

	void Move(float time);
	void ThirdPerson(float centerx, float centery, float centerz, float dist);
	void Mouse(sf::RenderWindow& window);
	void Look();
	void Look(float x, float y, float z);
};
