#ifndef __BOARD__
#define __BOARD__

#include <SFML/Graphics.hpp>

#define BOARD_SIZE_X 8
#define BOARD_SIZE_Y 8
#define SINGLE_BOARD_ITEM_SIZE 62.5

class Board
{
private:
	struct BoardItem
	{
		sf::RectangleShape background;
		sf::CircleShape item;
		sf::Color backgroundColor;
		sf::Color itemColor;
		bool isSet = false;
		bool isSelected = false;
		int x = -1, y = -1;
	};
public:
	struct Player
	{
		sf::Color color;
		int number;
		Player(int n, sf::Color c) : color(c), number(n) {}
	};

private:
	BoardItem m_board[BOARD_SIZE_X][BOARD_SIZE_Y];
	BoardItem* m_currentSelection = nullptr;

public:
	Board(Player*, Player*);

	void update(sf::Vector2f);

	void draw(sf::RenderWindow&);
};

#endif // !__BOARD__
