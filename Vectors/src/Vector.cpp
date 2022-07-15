//#include "Vector.h"
//
//Vector::Vector(float x, float y)
//{
//	this->_x = x;
//	this->_y = y;
//}
//
//float Vector::Magnitude()
//{
//	return sqrt(pow(_x, 2.0f)+ pow(_y, 2.0f));
//}
//
//Vector Vector::Normalized()
//{
//	Vector NormVec(0, 0);
//	NormVec._x = this->_x / this->Magnitude();
//	NormVec._y = this->_y / this->Magnitude();
//	return NormVec;
//
//}
//
//std::string Vector::CoordinatesString()
//{
//	return "(" + std::to_string(this->_x) + "," + std::to_string(this->_y) + ")";
//}





//#include <iostream>
//#include "Vector.h"
//
//#include "SFML/Main.hpp"
//#include "SFML/Graphics.hpp"
//
//
//int main()
//{
//    std::cout << "Hello World !\n";
//
//    Vector a(8, 7);
//
//    std::cout << "The vector is " << a.CoordinatesString() << std::endl;
//    std::cout << "It's magnitude is " << a.Magnitude() << std::endl;
//    std::cout << "The normalized vector is " << a.Normalized().CoordinatesString() << std::endl;
//    a.Normalized();
//
//    sf::RenderWindow window(sf::VideoMode(2160, 1080), "Tooltip test");
//    int alpha = 1;
//    sf::Clock clock;
//    sf::Clock secondClock;
//    sf::Clock deciiSecondClock;
//
//    sf::Time timeSinceLastUpdate = sf::Time::Zero;
//    window.setFramerateLimit(60);
//
//    sf::RectangleShape ooo;
//    ooo.setSize(sf::Vector2f(500.0f, 500.0f));
//
//
//    while (window.isOpen())
//    {
//        window.display();
//        window.draw(ooo);
//    }
//
//    return EXIT_SUCCESS;
//}