#include "GridManager.h"

GridManager::GridManager()
{
	cellWidth = ScreenWidth / columnCount;
	cellHeight = ScreenHeight / rowCount;

	for (int y = 0; y < rowCount; y++)
	{
		vector<Node*> row;
		for (int x = 0; x < columnCount; x++)
		{
			Node* node = new Node(x, y, cellWidth, cellHeight);
			row.push_back(node);
		}
		grid.push_back(row);
	}
}

void GridManager::DrawGrid(sf::RenderWindow& win)
{
	for (int y = 0; y < rowCount; y++)
	{
		for (int x = 0; x < columnCount; x++)
		{
			win.draw(grid[y][x]->shape);
		}
	}
}