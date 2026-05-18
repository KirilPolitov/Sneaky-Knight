#include <SFML/Graphics.hpp>
#include "jumpPad.hpp"
#include "coin.hpp"
#include <optional>
#include <vector>

int main() {
	srand(time(0));
	sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(videoMode, "sneaky knight");
	window.setVerticalSyncEnabled(true);
	sf::RectangleShape rectangle({ 50, 50 });
	rectangle.setPosition({ 200, 200 });
	rectangle.setFillColor(sf::Color::White);
	std::vector<sk::jumpPad> pads;
	pads.push_back(sk::jumpPad({ 1000, 700 }));
	pads.push_back(sk::jumpPad({ 700, 450 }));
	pads.push_back(sk::jumpPad({ 300, 450 }));
	std::vector <sk::coin> coins;
	coins.push_back(window);
	sf::Texture cube;
	if (cube.loadFromFile("cube.png")) {
		rectangle.setTexture(&cube);
	}
	sf::RectangleShape ground({ 1920, 200});
	ground.setPosition({ 0, 1000 });
	ground.setFillColor(sf::Color::Green);
	sf::Clock clock;
	sf::Vector2f movement = { 0, 0 };
	float gravity = 2000.f;
	float timeElapsed = 0;
	int collectedCoins = 0;
	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();
		timeElapsed += deltaTime;
		while (std::optional<sf::Event> opt = window.pollEvent()) {
			if (opt->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		
		if (timeElapsed > 5) {
			timeElapsed = 0;
			coins.push_back(window);
		}
		for (int i = 0; i < pads.size(); i++) {
			float distance = (coins[i].getGlobalCenter() - rectangle.getGlobalBounds().getCenter()).length();
			if (distance <= 25.f) {
				collectedCoins++;
				coins.erase(coins.begin() + i-1);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			movement.x = -600;
		}
		else movement.x = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			movement.x = 600;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x = 0;
		if (ground.getGlobalBounds().position.y > rectangle.getGlobalBounds().position.y + rectangle.getSize().y) {
			movement.y += (movement.y > 0) ? gravity * 1.5f * deltaTime : gravity * deltaTime;
		}
		else { 
			movement.y = 0;
			rectangle.setPosition({rectangle.getPosition().x, ground.getPosition().y - rectangle.getSize().y});
			for (int i = 0; i < pads.size(); i++) {
				pads[i].setAlpha(255);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			for (int i = 0; i < pads.size(); i++) {
				float distance = (pads[i].getGlobalCenter() - rectangle.getGlobalBounds().getCenter()).length();
				if (distance <= 50.f && !pads[i].getUsed()) {
					movement.y = -1000;
					pads[i].setUsed(true);
					pads[i].setAlpha(50);
					for (int j = 0; j < pads.size(); j++) {
						if (j != i) {
							pads[j].setUsed(false);
							pads[j].setAlpha(255);
						}
					}
				}
			}
			if (ground.getPosition().y - rectangle.getPosition().y <= rectangle.getSize().y) {
				movement.y = -1000;
				for (int i = 0; i < pads.size(); i++) {
					pads[i].setUsed(false);
					pads[i].setAlpha(255);
				}
			}
		}
		rectangle.move(movement * deltaTime);
		if (rectangle.getPosition().x < 0)
			rectangle.setPosition({ 0, rectangle.getPosition().y });
		else if (rectangle.getPosition().x > window.getSize().x - rectangle.getSize().x)
			rectangle.setPosition({ window.getSize().x - rectangle.getSize().x, rectangle.getPosition().y });
		window.clear(sf::Color(135, 206, 235));
		for (int i = 0; i < pads.size(); i++) {
			window.draw(pads[i].getShape());
		}
		for (int i = 0; i < coins.size(); i++) {
			window.draw(coins[i].getShape());
		}
		window.draw(rectangle);
		window.draw(ground);
		window.display();
	}
}