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
		const bool getUsed() const {
			return used;
		}
		const sf::Vector2f getGlobalCenter() const {
			return shape.getGlobalBounds().getCenter();
		}
		const sf::CircleShape& getShape() const {
			return shape;
		}
		void setAlpha(std::uint8_t alpha) {
			shape.setFillColor({ 0, 0, 255, alpha });
		}
	};
}