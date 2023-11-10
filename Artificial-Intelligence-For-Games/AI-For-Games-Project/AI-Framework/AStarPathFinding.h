#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

#include "SFML/Graphics.hpp"

using namespace std;

struct Node {
	Node(int _x, int _y, int cellWidth, int cellHeight, Node* _parent = nullptr);
	int x, y;
	int f, g, h;
	Node* parent;
	void calculateH(int destX, int destY);
	void calculateF();
	sf::RectangleShape shape;

	int width;
	int height;
};
