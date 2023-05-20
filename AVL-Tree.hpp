#pragma once

#include <iostream>

using std::cout;
using std::endl;

struct Node
{
	Node*	left;
	Node*	right;
	int		height;
	int		data;

	Node(int new_data) : left(nullptr), right(nullptr), height(1), data(new_data) {}
};

class AVL
{
public:
	AVL();
	~AVL();

	void	Insert(int data);
	void	Delete(int data);
	Node*	Search(int data);

	void	Inorder_Traversal();
	void	Preorder_Traversal();
	void	Postorder_Traversal();


private:
	Node*	root;

	Node*	Insert_hepler(Node* node, int data);
	int		Max(int a, int b);
	int		Height(Node* node);

	Node*	Delete_helper(Node* node, int data);

	Node*	MinNode(Node* node);
	Node*	MaxNode(Node* node);

	int		BalanceFactor(Node* node);

	Node*	Search_helper(Node* node, int data);

	Node*	Left_Rotate(Node* x);
	Node*	Right_Rotate(Node* x);

	void	Inorder_Traversal_helper(Node* node);
	void	Preorder_Traversal_helper(Node* node);
	void	Postorder_Traversal_helper(Node* node);
};