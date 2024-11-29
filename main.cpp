#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Box.h"

using namespace std;

// Sort Visualizer
int main() {
	// Seed with a real random value
	std::random_device rd;

	// Create a random number generator
	std::mt19937 gen(rd());

	//// Define the range for random numbers (e.g., 0.0 to 1.0)
	//std::uniform_real_distribution<> distr(1, 100);

	// Vector of 100 random numbers
	vector<int> arr(100);
	for (int i = 0; i < arr.size(); ++i) {
		arr[i] = i+1;
	}
	shuffle(arr.begin(), arr.end(), gen);

	// Initialize window ----------------------------------------------------------------
	sf::RenderWindow window(sf::VideoMode(1440, 1080), "SFML works!");

	sf::Clock clock;

	bool started = false;

	sf::RectangleShape button(sf::Vector2f(256, 128));
	button.setPosition(sf::Vector2f((float)window.getSize().x / 2.0 - 128, (float)window.getSize().y * 4 / 5));
	button.setFillColor(sf::Color::Green);
	qt::Box<float> buttonBox(button.getPosition(), button.getSize());

	// Sort Variables
	const int speed = 1;
	int i = 0;
	int j = 0;

	// Rectangle Array
	vector<sf::RectangleShape> rarr(100);
	for (int i = 0; i < arr.size(); i++) {
		sf::RectangleShape arrItem(sf::Vector2f((float)window.getSize().x * 10.0 / 12.0 / arr.size(), (float)window.getSize().y * 8 / 10.0 * (float)arr[i] / 100.0));
		arrItem.setPosition(sf::Vector2f((float)window.getSize().x / 12.0 + (float)window.getSize().x * 10.0 / 12.0 / arr.size() * i,
			(float)window.getSize().y * 1.0 / 10.0 + (float)window.getSize().y * 8 / 10.0 * (1 - (float)arr[i] / 100.0)));
		if (i == j || i == j + 1)
			arrItem.setFillColor(Color::Green);
		rarr[i] = arrItem;
	}

	while (window.isOpen()) {
		// Get Delta Time
		sf::Time dt = clock.restart();

		// Window events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Code here

		// Button Press
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			if (buttonBox.contains((Vector2f)mousePos)) {
				started = true;
			}
		}

		// Sort Segment

		if (started && i < 100) {
			if (i < arr.size() - 1) {

				if (arr[j] > arr[j + 1]) {
					int temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;

					// swap x pos value in rarr
					float xtemp = rarr[j].getPosition().x;
					rarr[j].setPosition(sf::Vector2f(rarr[j + 1].getPosition().x, rarr[j].getPosition().y));
					rarr[j + 1].setPosition(sf::Vector2f(xtemp, rarr[j + 1].getPosition().y));

					// swap arr index in rarr
					sf::RectangleShape rtemp = rarr[j];
					rarr[j] = rarr[j+1];
					rarr[j+1] = rtemp;
				}
				// Reset the current rectangle color to White
				rarr[j].setFillColor(Color::White);

				// Move to the next rectangle
				j++;

				// Check if the inner loop has finished
				if (j == arr.size() - i - 1) {
					// Finalize the last unsorted item in this pass
					rarr[arr.size() - i - 1].setFillColor(Color::White);

					// Reset `j` for the next pass
					j = 0;

					// Move to the next outer loop iteration
					i++;

					// Highlight the next unsorted item (if any) in Green
					if (i < arr.size() - 1) {
						rarr[j].setFillColor(Color::Green);
					}
				}
				else {
					// Highlight the next rectangle in Green
					rarr[j].setFillColor(Color::Green);
				}
			}
		}

		// Draw
		window.clear();


		for (sf::RectangleShape rect : rarr) {
			window.draw(sf::RectangleShape(rect));
		}

		if (!started)
			window.draw(button);

		window.display();
	}
	return 0;
};