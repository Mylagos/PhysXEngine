#include "Entity.h"

Entity::Entity(std::unique_ptr<sf::Shape> shape) : shapePtr_(std::move(shape))
{
	bodyPtr_ = std::make_unique<RigidBody>();
}

Entity::Entity(sf::CircleShape shape, Vector2D position, float radius, float mass)
{
	bodyPtr_ = std::make_unique<RigidBody>(position, radius, mass);
	
	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	shapePtr_=std::make_unique<sf::CircleShape>(shape);
}

Entity::Entity(sf::RectangleShape shape, Vector2D position, Vector2D widthToHeight, float mass)
{
	bodyPtr_ = std::make_unique<RigidBody>(position, widthToHeight, mass);

	shape.setSize(sf::Vector2f(widthToHeight.X(), widthToHeight.Y()));
	shape.setOrigin(widthToHeight.X(), widthToHeight.Y());
	shapePtr_ = std::make_unique<sf::RectangleShape>(shape);
}

Entity::Entity(sf::RectangleShape shape, Vector2D position, Vector2D widthToHeight, float mass, float radius)
{
	bodyPtr_ = std::make_unique<RigidBody>(position, widthToHeight, mass, radius);

	shape.setSize(sf::Vector2f(widthToHeight.X(), widthToHeight.Y()));
	shape.setOrigin(widthToHeight.X()/2, widthToHeight.Y()/2);
	shapePtr_ = std::make_unique<sf::RectangleShape>(shape);
}


void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*shapePtr_, states);
}

void Entity::EntityToSfmlPos(const sf::RenderWindow& window) const
{
	shapePtr_->setPosition(Utilities::WorldToSfmlPos(this->bodyPtr_->getPosition(), window));
}

//Vector2D Entity::rbToEntityCenterOrigin() const
//{
//	Vector2D temp;
//
//	//Sets the origin to the center of the SFML shape instead of top left
//	temp.SetX(bodyPtr_->getPosition().X() + bodyPtr_->getSize().X()/2.0f);
//	temp.SetY(bodyPtr_->getPosition().Y() + bodyPtr_->getSize().Y()/2.0f);
//
//	return temp;
//}