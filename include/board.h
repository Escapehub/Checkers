#ifndef __BOARD__
#define __BOARD__

#include <SFML/Graphics.hpp>

#define BOARD_SIZE_X 8
#define BOARD_SIZE_Y 8
#define SINGLE_BOARD_ITEM_SIZE 62.5

namespace BoardController
{
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

	struct Player
	{
		sf::Color color;
		int number;
		Player(int n, sf::Color c) : color(c), number(n) {}
	};

	class Board
	{
	private:
		BoardItem m_board[BOARD_SIZE_X][BOARD_SIZE_Y];
		BoardItem* m_currentSelection = nullptr;

	public:
		/**
		* Create board object
		* 
		* \param Player* pointer to player 1 object
		* \param Player* pointer to player 2 object
		*/
		Board(Player*, Player*);
		
		/**
		* Update board on mouse click
		* 
		* \param Player* pointer to current player object
		* \param sf::Vector2f mouse position on window
		*/
		void update(Player*, sf::Vector2f);

		/**
		* Draw board and items to the screen
		* 
		* \param sf::RenderWindow& reference to window object
		*/
		void draw(sf::RenderWindow&);
	};
}
#endif // !__BOARD__
