#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Engine.h"

class VisualWorld
{
private:
	sf::RenderWindow window_;
	std::vector<Entity> entities_;
	sf::Mouse mouse_;
	Engine engine_;

	int i = 0;
	float x = 0;
	bool isOverMax = false;
public:
	VisualWorld();
	~VisualWorld();

	void UpdatePhysics() const;
	void Draw();
	void WorldLoop();
	void Events();
};