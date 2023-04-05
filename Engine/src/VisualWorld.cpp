#include "VisualWorld.h"

#include <tracy/Tracy.hpp>


VisualWorld::VisualWorld()
{
	window_.create(sf::VideoMode(2160, 1080), "Physics engine");

	view_ = window_.getDefaultView();

	int x = window_.getPosition().x;

	std::cout << window_.getPosition().x << " " << window_.getPosition().y << std::endl;
	//window_.setFramerateLimit(60);
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
		case sf::Event::KeyPressed:
			if (MyEvent.key.code == sf::Keyboard::W)
			{
				view_.move(0.0f, -5.0f);
			}
			if (MyEvent.key.code == sf::Keyboard::S)
			{
				view_.move(0.0f, 5.0f);
			}
			if (MyEvent.key.code == sf::Keyboard::D)
			{
				view_.move(5.0f, 0.0f);
			}
			if (MyEvent.key.code == sf::Keyboard::A)
			{
				view_.move(-5.0f, 0.0f);
			}
			if (MyEvent.key.code == sf::Keyboard::E)
			{
				view_.zoom(2.0f);
			}
			if (MyEvent.key.code == sf::Keyboard::C)
			{
				view_.zoom(0.5f);
			}
		case sf::Event::MouseButtonPressed:
			if (MyEvent.mouseButton.button == sf::Mouse::Left)
			{
				sf::CircleShape circleShape;
				int i = 0;
				entities_.emplace_back(circleShape,
					Vector2D(mouse_.getPosition(window_).x,
						1080 - mouse_.getPosition(window_).y), 50.0f, 1.0f);
				i++;
			}
			if (MyEvent.mouseButton.button == sf::Mouse::Right)
			{
				sf::RectangleShape rectangleShape;
				i++;
				rectangleShape.rotate(20.0f * i);
				entities_.emplace_back(rectangleShape,
					Vector2D(mouse_.getPosition(window_).x,
						1080 - mouse_.getPosition(window_).y),
					Vector2D(50 * (i * 0.25f), 50 * (i * 0.25f)), 1.0f, 20.0f * i);

			}

			break;
		case sf::Event::Closed:
			window_.close();
			break;
		case sf::Event::MouseMoved:
		{
			/*Vector2D MyVec;
			MyVec = Utilities::SfmlToWorldPos(Vector2D(mouse_.getPosition(window_).x,
				1080 - mouse_.getPosition(window_).y), window_);
			std::cout << "Mouse pos : " << MyVec.X() << " : " << MyVec.Y() << std::endl;
			break;*/
		}
		default:

			break;
		}
	}
}

void VisualWorld::WorldLoop()
{
	int i = 0;
	while (window_.isOpen()) {

		Events();
		while (i < 50) {
			sf::RectangleShape rectangleShape;
			rectangleShape.rotate(20.0f * i);
			entities_.emplace_back(rectangleShape,
				Vector2D(0, i),
				Vector2D(50 * (i * 0.25f), 50 * (i * 0.25f)), 1.0f, 20.0f * i);
			i++;
		}
		i = 0;
		UpdatePhysics();
		window_.setView(view_);

		fps_.update();
		std::ostringstream ss;
		ss << fps_.getFPS();

		window_.setTitle(ss.str());

		//Draw();


	}
}

void VisualWorld::Draw()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
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
#ifdef TRACY_ENABLE
	FrameMark;
#endif
}
