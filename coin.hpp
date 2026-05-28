#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

namespace sk {
	class coin {
		sf::CircleShape shape;
		float lifetime;
	public:
		coin(sf::RenderWindow& window) :
			shape(25.f),
			lifetime(0.f) {
			shape.setFillColor(sf::Color::Yellow);
			shape.setOutlineThickness(2.f);
			shape.setOutlineColor({ 200, 160, 0 });
			float diameter = shape.getRadius() * 2.f;
			int maxRangeX = static_cast<int>(window.getSize().x - diameter);
			int maxRangeY = static_cast<int>(window.getSize().y - 300);
			if (maxRangeX <= 0) maxRangeX = 1;
			if (maxRangeY <= 0) maxRangeY = 1;
			float posX = static_cast<float>(rand() % maxRangeX);
			float posY = static_cast<float>(rand() % maxRangeY);
			shape.setPosition({ posX, posY });
		}

		const sf::CircleShape& getShape() const {
			return shape;
		}

		const sf::Vector2f getGlobalCenter() const {
			return shape.getGlobalBounds().getCenter();
		}
		void addLifetime(float deltaTime) {
			lifetime += deltaTime;
		}
		void setLifetime(float lifetime) {
			this->lifetime = lifetime;
		}
		const float getLifetime() const {
			return lifetime;
		}
	};
}