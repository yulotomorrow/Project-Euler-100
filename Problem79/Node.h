#pragma once
#include <vector>

struct Node
{
	int digit;
	std::vector<struct node*> nodes;
	Node(int value) 
	{
		digit = value;
		nodes = {};
	}
};
