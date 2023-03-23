#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Engine.h"
#include "FpsCounter.h"
#include <sstream>

class VisualWorld
{
private:
	sf::RenderWindow window_;
	std::vector<Entity> entities_;
	sf::Mouse mouse_;
	sf::View view_;
	Engine engine_;
	FPS fps_;

	int i = 0;
	float x = 0;
	bool isOverMax = false;
public:
	VisualWorld();
	~VisualWorld() = default;

	void UpdatePhysics() const;
	void Draw();
	void WorldLoop();
	void Events();
};