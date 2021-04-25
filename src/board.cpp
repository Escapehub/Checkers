#include "board.h"

Board::Board()
{
    sf::Color currentColor = sf::Color::Black;

    for (int x = 0; x < BOARD_SIZE_X; ++x)
        for (int y = 0; y < BOARD_SIZE_Y; ++y)
        {
            /* Get pointer to current board item */
            BoardItem* currentItem = &this->m_board[x][y];

            /* Set background color and position */
            currentItem->background.setSize(sf::Vector2f(SINGLE_BOARD_ITEM_SIZE, SINGLE_BOARD_ITEM_SIZE));
            currentItem->backgroundColor = currentColor;
            currentItem->background.setFillColor(this->m_board[x][y].backgroundColor);
            currentItem->background.setPosition(sf::Vector2f(SINGLE_BOARD_ITEM_SIZE * x, SINGLE_BOARD_ITEM_SIZE * y));

            /* Set item (chip) background and position*/
            currentItem->item.setRadius(SINGLE_BOARD_ITEM_SIZE / 2);
            currentItem->item.setPosition(sf::Vector2f(SINGLE_BOARD_ITEM_SIZE * x, SINGLE_BOARD_ITEM_SIZE * y));
            currentItem->itemColor = currentColor;
            currentItem->item.setFillColor(currentItem->itemColor);

            /* Player 1 chips */
            if (
                (x == 1 && y == 0) || (x == 3 && y == 0) || (x == 5 && y == 0) || (x == 7 && y == 0) || // row 1
                (x == 0 && y == 1) || (x == 2 && y == 1) || (x == 4 && y == 1) || (x == 6 && y == 1) || // row 2
                (x == 1 && y == 2) || (x == 3 && y == 2) || (x == 5 && y == 2) || (x == 7 && y == 2)    // row 3
                ) 
            {
                currentItem->itemColor = sf::Color::Blue;
                currentItem->item.setFillColor(currentItem->itemColor);
                currentItem->isSet = true;
            }

            /* Player 2 chips */
            if (
                (x == 0 && y == 5) || (x == 2 && y == 5) || (x == 4 && y == 5) || (x == 6 && y == 5) || // row 1
                (x == 1 && y == 6) || (x == 3 && y == 6) || (x == 5 && y == 6) || (x == 7 && y == 6) || // row 2
                (x == 0 && y == 7) || (x == 2 && y == 7) || (x == 4 && y == 7) || (x == 6 && y == 7)    // row 3
                ) 
            {
                currentItem->itemColor = sf::Color::Red;
                currentItem->item.setFillColor(currentItem->itemColor);
                currentItem->isSet = true;
            }

            if (y != BOARD_SIZE_Y - 1)
            {
                if (currentColor == sf::Color::Black)
                    currentColor = sf::Color::White;
                else
                    currentColor = sf::Color::Black;
            }
        }
}

void Board::update(sf::Vector2f windowCoords)
{
    for (int x = 0; x < BOARD_SIZE_X; ++x)
        for (int y = 0; y < BOARD_SIZE_Y; ++y)
        {
            /* Get pointer to current board item */
            BoardItem* currentItem = &this->m_board[x][y];

            if (currentItem->background.getGlobalBounds().contains(windowCoords))
            {

                if (this->m_currentSelection == nullptr && currentItem->isSet)
                {
                    currentItem->background.setFillColor(sf::Color(128, 128, 128));
                    this->m_currentSelection = currentItem;
                }
                else if (this->m_currentSelection == currentItem)
                {
                    currentItem->background.setFillColor(currentItem->backgroundColor);
                    this->m_currentSelection = nullptr;
                }

                /* Found the item needed, no need to check the others */
                return;
            }
        }
}

void Board::draw(sf::RenderWindow& window)
{
    for (int x = 0; x < BOARD_SIZE_X; ++x)
        for (int y = 0; y < BOARD_SIZE_Y; ++y)
        {
            window.draw(this->m_board[x][y].background);
            window.draw(this->m_board[x][y].item);
        }
}
