#pragma once

#include <iostream>
#include "Vector2D.h"
#include "RigidBody.h"

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "VisualWorld.h"

int main()
{
    
    VisualWorld world;
    world.WorldLoop();

    return EXIT_SUCCESS;
}


//sf::RenderWindow window();
    //sf::Clock clock;

    //sf::CircleShape ooo(50);
    ////sf::RectangleShape oooeee(sf::Vector2f<50, 50>);
    ////ooo.setRadius(50.0f);
    ////ooo.setPosition(-25, -25);
    //sf::CircleShape eee;
    //eee.setRadius(25.0f);
    ////eee.setPosition(25.f,25.f);
    //eee.setFillColor(sf::Color::Red);

    //window.setFramerateLimit(60);


    //while (window.isOpen())
    //{
    //    window.clear();
    //    sf::Vector2f temppos = ooo.getPosition();
    //    temppos += sf::Vector2f(3, 2);
    //    //ooo.setPosition(temppos);
    //    window.draw(ooo);
    //    window.draw(eee);
    //    window.display();

    //    sf::Time deltatime = clock.restart();
    //    sf::Event event;
    //    while (window.pollEvent(event))
    //    {
    //        switch (event.type)
    //        {
    //        case sf::Event::Closed:
    //            window.close();
    //            break;
    //        default:
    //            break;
    //        }
    //    }
    //}