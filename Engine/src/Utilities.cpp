#include "Utilities.h"

sf::Vector2f Utilities::WorldToSfmlPos(Vector2D worldPos, const sf::RenderWindow& window)
{
	return { worldPos.X(),  window.getSize().y - worldPos.Y() };
}

Vector2D Utilities::SfmlToWorldPos(Vector2D worldPos, const sf::RenderWindow& window)
{
	return { worldPos.X(),  window.getSize().y + worldPos.Y() };
}