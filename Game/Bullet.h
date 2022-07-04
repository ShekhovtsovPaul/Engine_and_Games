#pragma once

#include <glm/glm.hpp>
#include <SpriteBatch.h>


class Bullet {
public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
	~Bullet();

	void draw(Engine::SpriteBatch& spriteBatch);
	bool update();

private:

	int _lifeTime;
	float _speed;	// how far per/frame
	glm::vec2 _direction;
	glm::vec2 _position;
};
