#pragma once
#include "AStarPathFinding.h"

#include "SFML/Graphics.hpp"

#include "Constants.h"

class GridManager
{
public:
	GridManager();

	void DrawGrid(sf::RenderWindow& win);

	// Check if a node is valid and not blocked
	bool isValid(int y, int x) {
		int n = grid.size();
		int m = grid[0].size();
		if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == nullptr)
			return false;
		return true;
	}

	// Check if a node is in the closed set
	bool isInClosedSet(int x, int y, vector<Node*>& closedSet) {
		for (auto& node : closedSet) {
			if (node->x == x && node->y == y)
				return true;
		}
		return false;
	}

	// Get the node with the lowest f value in the open set
	Node* getLowestFNode(vector<Node*>& openSet) {
		Node* lowestFNode = openSet[0];
		for (auto& node : openSet) {
			if (node->f < lowestFNode->f)
				lowestFNode = node;
		}
		return lowestFNode;
	}

	sf::Vector2f getGridPosition(float x, float y)
	{
		int cellX = floor(x / cellWidth);
		int cellY = floor(y / cellHeight);

		return sf::Vector2f(cellX, cellY);
	}

	// Get the neighbors of a node
	vector<Node*> getNeighbors(Node* node, int destX, int destY) {
		vector<Node*> neighbors;
		int dx[] = { 0, 0, -1, 1 };
		int dy[] = { -1, 1, 0, 0 };
		for (int i = 0; i < 4; i++) {
			int x = node->x + dx[i];
			int y = node->y + dy[i];
			if (isValid(x, y)) {
				Node* neighbor = grid[y][x];
				neighbor->g = node->g + 1;
				neighbor->calculateH(destX, destY);
				neighbor->calculateF();
				neighbors.push_back(neighbor);
			}
		}
		return neighbors;
	}

	// A* pathfinding algorithm
	vector<Node*> aStarPathfinding(int startX, int startY, int destX, int destY) {
		for (std::vector<Node*> row : grid)
		{
			for (auto node : row)
			{
				node->f = 0;
				node->g = 0;
				node->h = 0;
				node->parent = nullptr;
			}
		}

		vector<Node*> path;
		vector<Node*> openSet;
		vector<Node*> closedSet;
		auto startNode = grid[startY][startX];
		startNode->calculateH(destX, destY);
		startNode->calculateF();
		openSet.push_back(startNode);

		while (!openSet.empty()) {
			Node* currentNode = getLowestFNode(openSet);
			if (currentNode->x == destX && currentNode->y == destY) {
				// Destination node has been reached, construct the path
				while (currentNode != nullptr) {
					path.push_back(currentNode);
					currentNode->shape.setFillColor(sf::Color(0, 0, 255, 128));
					currentNode = currentNode->parent;
				}
				return path; // Add this line to return the path
			}

			// Move the current node from the open set to the closed set
			openSet.erase(remove(openSet.begin(), openSet.end(), currentNode), openSet.end());
			closedSet.push_back(currentNode);

			// Get the neighbors of the current node
			vector<Node*> neighbors = getNeighbors(currentNode, destX, destY);

			if (neighbors.empty())
			{
				neighbors = getNeighbors(currentNode, destX, destY);
			}

			// Process each neighbor
			for (auto& neighbor : neighbors) {
				// Skip neighbors in the closed set
				if (isInClosedSet(neighbor->x, neighbor->y, closedSet))
					continue;

				// Calculate the tentative g score
				int tentativeGScore = currentNode->g + 1;

				// Add the neighbor to the open set if it is not there
				if (!count(openSet.begin(), openSet.end(), neighbor))
					openSet.push_back(neighbor);

				// Otherwise, update the g score if it is lower than the current g score
				else if (tentativeGScore >= neighbor->g)
					continue;

				// This path is the best until now. Record it!
				neighbor->parent = currentNode;
				neighbor->g = tentativeGScore;
				neighbor->calculateF();
			}
		}

		// No path exists
		return path;
	}

private:
	vector<vector<Node*>> grid;

	const int columnCount = 40;
	const int rowCount = 20;

	int cellWidth;
	int cellHeight;
};
