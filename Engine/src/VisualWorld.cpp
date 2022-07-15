#include "VisualWorld.h"

VisualWorld::VisualWorld()
{
	window_.create(sf::VideoMode(2160, 1080), "Physics engine");
	
	int x = window_.getPosition().x;
	
	std::cout << window_.getPosition().x << " " << window_.getPosition().y << std::endl;
	window_.setFramerateLimit(60);
	//entities_ = std::vector<Entity>&;
}

VisualWorld::~VisualWorld()
{
	
}


void VisualWorld::UpdatePhysics() const
{
	Engine::update_physics();
}

void VisualWorld::Events()
{
	sf::Event event;
	while (window_.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::CircleShape ooo;
				int i = 0;
				entities_.emplace_back(Entity(ooo, Vector2D(mouse_.getPosition(window_).x, 1080-mouse_.getPosition(window_).y), 50, 1));

				//std::cout << "mouse pos : "<< mouse_.getPosition(window_).x << " " << mouse_.getPosition(window_).y << std::endl;
				i++;
			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				sf::RectangleShape eee;
				i++;
				eee.rotate(20*i);
				entities_.emplace_back(Entity(eee, Vector2D(mouse_.getPosition(window_).x,  1080 - mouse_.getPosition(window_).y), Vector2D(50*(i*0.25f),50*(i * 0.25f)), 1, 20.0f*i));

				//std::cout << "mouse pos : "<< mouse_.getPosition(window_).x << " " << mouse_.getPosition(window_).y << std::endl;
				//RectCollider* oeeoeo = dynamic_cast<RectCollider*>(entities_.at(i).getBody().getCollider());
				/*sf::RectangleShape iii;
				iii.setSize(sf::Vector2f(500, 500));
				iii.setPosition(sf::Vector2f(500, 1000));
				iii.setOrigin(sf::Vector2f(250, 250));
				iii.setRotation(20 * i);
				window_.draw(iii);*/
				/*for (int j=0; j< oeeoeo->ReturnPoints().size();j++)
				{
					sf::CircleShape aaa;
					aaa.setRadius(2);
					aaa.setFillColor(sf::Color::Yellow);
					aaa.setPosition(sf::Vector2f(oeeoeo->ReturnPoints().at(j).X(), 1080-oeeoeo->ReturnPoints().at(j).Y()));
					window_.draw(aaa);
				}*/
				
			}

			break;
		case sf::Event::Closed:
			window_.close();
			break;
		default:
			break;
		}
	}
}

void VisualWorld::WorldLoop()
{
	while (window_.isOpen()){
		//DE LA MERDE
		/*sf::CircleShape eee;
		
		x+=0.05f;
		entities_.emplace_back(eee, Vector2D(1100+sin(x)*500, 500+cos(x)*500), 50.0f, 1);
		engine_.setGravity(x);*/
		//FIN MERDE

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
