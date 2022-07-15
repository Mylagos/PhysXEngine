#pragma once
#include "RigidBody.h"
#include "SFML/Graphics.hpp"
#include "Utilities.h"

class Entity : public sf::Drawable, public sf::Transformable
{
private:
	std::unique_ptr<RigidBody> bodyPtr_;
	std::unique_ptr<sf::Shape> shapePtr_;
public:
	Entity(std::unique_ptr<sf::Shape>);
	Entity(sf::CircleShape, Vector2D, float, float);
	Entity(sf::RectangleShape, Vector2D, Vector2D, float);
	Entity(sf::RectangleShape, Vector2D, Vector2D, float, float);

	void EntityToSfmlPos(const sf::RenderWindow& window) const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const RigidBody& getBody() const { return *bodyPtr_; }
	void setFillColor(sf::Color color) const { shapePtr_->setFillColor(color); }


	//Vector2D rbToEntityCenterOrigin() const;
};