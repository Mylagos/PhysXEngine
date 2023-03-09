#include "VisualWorld.h"

VisualWorld::VisualWorld()
{
	window_.create(sf::VideoMode(2160, 1080), "Physics engine");
	
	int x = window_.getPosition().x;
	
	std::cout << window_.getPosition().x << " " << window_.getPosition().y << std::endl;
	window_.setFramerateLimit(60);
}

void VisualWorld::UpdatePhysics() const
{

	Engine::update_physics();
}

void VisualWorld::Events()
{
	sf::Event MyEvent{};
	while (window_.pollEvent(MyEvent))
	{
		switch (MyEvent.type)
		{
		case sf::Event::MouseButtonPressed:
			if (MyEvent.mouseButton.button == sf::Mouse::Left)
			{
				sf::CircleShape circleShape;
				int i = 0;
				entities_.emplace_back(circleShape, 
					Vector2D(mouse_.getPosition(window_).x, 
						1080-mouse_.getPosition(window_).y), 50.0f, 1.0f);
				i++;
			}
			if (MyEvent.mouseButton.button == sf::Mouse::Right)
			{
				sf::RectangleShape rectangleShape;
				i++;
				rectangleShape.rotate(20.0f*i);
				entities_.emplace_back(rectangleShape, 
					Vector2D(mouse_.getPosition(window_).x,  
						1080 - mouse_.getPosition(window_).y), 
					Vector2D(50*(i*0.25f),50*(i * 0.25f)), 1.0f, 20.0f*i);
				
			}

			break;
		case sf::Event::Closed:
			window_.close();
			break;
		case sf::Event::MouseMoved:
			{
				Vector2D MyVec;
				MyVec = Utilities::SfmlToWorldPos(Vector2D(mouse_.getPosition(window_).x,
					1080 - mouse_.getPosition(window_).y), window_);
				std::cout << "Mouse pos : " << MyVec.X() << " : " << MyVec.Y() << std::endl;
				break;
			}
		default:
			break;
		}
	}
}

void VisualWorld::WorldLoop()
{
	while (window_.isOpen()){
		Events();
		UpdatePhysics();
		Draw();
	}
}

void VisualWorld::Draw()
{
	window_.clear();
	for (auto& entity : entities_)
	{
		entity.setFillColor(sf::Color::White);
		entity.EntityToSfmlPos(window_);
		if (entity.getBody().getColliding() == true)
			entity.setFillColor(sf::Color::Red);
		entity.draw(window_, sf::RenderStates::Default);
	}
	window_.display();
}
