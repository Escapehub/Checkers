#include "board.h"

using namespace BoardController;

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Checkers");

	Player* p1 = new Player(1, sf::Color::Yellow);
	Player* p2 = new Player(2, sf::Color::Cyan);

	printf("%p, %p\n", p1, p2);

	Board* board = new Board(p1, p2);

	Player* currentPlayer = p1;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			if (event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left)
				board->update(currentPlayer, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		}

		window.clear();
		board->draw(window);
		window.display();
	}

	return 0;
}