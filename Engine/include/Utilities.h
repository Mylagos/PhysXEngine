#pragma once
#include "SFML/Graphics.hpp"
#include "Vector2D.h"

namespace Utilities
{
	sf::Vector2f WorldToSfmlPos(Vector2D worldPos, const sf::RenderWindow& window);
	Vector2D SfmlToWorldPos(Vector2D worldPos, const sf::RenderWindow& window);

	class FpsCounter
	{
	public:
		sf::Clock fpsClock_;

		void showFps(float deltaTime);
	};
}
