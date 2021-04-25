#include "board.h"

BoardController::Board::Board(Player* p1, Player* p2)
{
    sf::Color currentColor = sf::Color::Black;

    for (int x = 0; x < BOARD_SIZE_X; ++x)
        for (int y = 0; y < BOARD_SIZE_Y; ++y)
        {
            /* Get pointer to current board item */
            BoardItem* currentItem = &this->m_board[x][y];

            /* Setting position in array */
            currentItem->x = x;
            currentItem->y = y;

            /* Set background color and position */
            currentItem->background.setSize(sf::Vector2f(SINGLE_BOARD_ITEM_SIZE, SINGLE_BOARD_ITEM_SIZE));
            currentItem->backgroundColor = currentColor;
            currentItem->background.setFillColor(this->m_board[x][y].backgroundColor);
            currentItem->background.setPosition(sf::Vector2f(SINGLE_BOARD_ITEM_SIZE * x, SINGLE_BOARD_ITEM_SIZE * y));

            /* Set item (chip) background and position */
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
                currentItem->itemColor = p1->color;
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
                currentItem->itemColor = p2->color;
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

void BoardController::Board::update(Player* player, sf::Vector2f windowCoords)
{
    for (int x = 0; x < BOARD_SIZE_X; ++x)
        for (int y = 0; y < BOARD_SIZE_Y; ++y)
        {
            /* Get pointer to current board item */
            BoardItem* currentItem = &this->m_board[x][y];

            if (currentItem->background.getGlobalBounds().contains(windowCoords))
            {
                /* Chip interaction */
                if (this->m_currentSelection == nullptr && currentItem->isSet) /* Selecting */
                {
                    currentItem->background.setFillColor(sf::Color(128, 128, 128));
                    this->m_currentSelection = currentItem;
                }
                else if (this->m_currentSelection == currentItem) /* Deselecting */
                {
                    currentItem->background.setFillColor(currentItem->backgroundColor);
                    this->m_currentSelection = nullptr;
                }

                /* Chip movement */
                if (this->m_currentSelection != nullptr)
                {
                    if (player->number == 1)
                    {
                        if ((this->m_currentSelection->x + 1 == currentItem->x || this->m_currentSelection->x - 1 == currentItem->x) 
                            && this->m_currentSelection->y + 1 == currentItem->y)
                        {
                            if (currentItem->isSet)
                                return;
                            this->m_currentSelection->item.setFillColor(this->m_currentSelection->backgroundColor);
                            this->m_currentSelection->background.setFillColor(this->m_currentSelection->backgroundColor);
                            this->m_currentSelection->isSet = false;
                            this->m_currentSelection = nullptr;

                            currentItem->item.setFillColor(player->color);
                            currentItem->isSet = true;
                        }
                    }

                    if (player->number == 2)
                    {
                        if ((this->m_currentSelection->x + 1 == currentItem->x || this->m_currentSelection->x - 1 == currentItem->x)
                            && this->m_currentSelection->y - 1 == currentItem->y)
                        {
                            if (currentItem->isSet)
                                return;
                            this->m_currentSelection->item.setFillColor(this->m_currentSelection->backgroundColor);
                            this->m_currentSelection->background.setFillColor(this->m_currentSelection->backgroundColor);
                            this->m_currentSelection->isSet = false;
                            this->m_currentSelection = nullptr;

                            currentItem->item.setFillColor(player->color);
                            currentItem->isSet = true;
                        }
                    }
                }

                /* Found the item needed, no need to check the others */
                return;
            }
        }
}

void BoardController::Board::draw(sf::RenderWindow& window)
{
    for (int x = 0; x < BOARD_SIZE_X; ++x)
        for (int y = 0; y < BOARD_SIZE_Y; ++y)
        {
            window.draw(this->m_board[x][y].background);
            window.draw(this->m_board[x][y].item);
        }
}
