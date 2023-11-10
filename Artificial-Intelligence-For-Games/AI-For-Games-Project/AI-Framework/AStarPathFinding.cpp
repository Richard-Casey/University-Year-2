#include "AStarPathFinding.h"

Node::Node(int _x, int _y, int cellWidth, int cellHeight, Node* _parent) {
	x = _x;
	y = _y;
	parent = _parent;
	f = g = h = 0;

	width = cellWidth;
	height = cellHeight;

	shape.setSize(sf::Vector2f(cellWidth, cellHeight));
	shape.setPosition(_x * cellWidth, _y * cellHeight);
	shape.setFillColor(sf::Color::Transparent);
	/*shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(1.0f);*/
}

// Calculate the heuristic value (Manhattan distance)
void Node::calculateH(int destX, int destY) {
	h = abs(x - destX) + abs(y - destY);
}

// Calculate the f value (g + h)
void Node::calculateF() {
	f = g + h;
}