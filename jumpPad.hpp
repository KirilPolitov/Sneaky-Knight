//currently unused because im too lazy to replace everything

#pragma once
#include <SFML/Graphics.hpp>

namespace sk {
	class jumpPad {
		sf::CircleShape shape;
		bool used;
	public:
		jumpPad(sf::Vector2f location) :
			shape(50),
			used(false) {
			shape.setPosition(location);
			shape.setFillColor(sf::Color::Blue);
			shape.setOutlineColor(sf::Color::Yellow);
			shape.setOutlineThickness(5);
		};
		void setUsed(bool used) {
			this->used = used;
		}
		bool getUsed() {
			return used;
		}
		sf::Vector2f getGlobalCenter() {
			return shape.getGlobalBounds().getCenter();
		}
		sf::CircleShape& getShape() {
			return shape;
		}
	};
}