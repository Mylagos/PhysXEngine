#include "Utilities.h"

sf::Vector2f Utilities::WorldToSfmlPos(Vector2D worldPos, const sf::RenderWindow& window)
{
	//std::cout << worldPos.X() << " " << window.getSize().y - worldPos.Y() << std::endl;

	return { worldPos.X(),  window.getSize().y - worldPos.Y() };
}