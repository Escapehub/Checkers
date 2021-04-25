#include "board.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Checkers");

	Board* board = new Board();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			if (event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left)
				board->update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		}

		window.clear();
		board->draw(window);
		window.display();
	}

	return 0;
}