#include "./AVL-Tree.hpp"

/********************/
/*		Public		*/
/********************/

AVL::AVL()
{
	this->root = nullptr;
}

AVL::~AVL()
{
	//
}

void	AVL::Insert(int data)
{
	Node*	tmp_root = this->root;
	this->root = Insert_hepler(tmp_root, data);
}

void	AVL::Delete(int data)
{
	if (!this->root)
	{
		cout << "AVL-Tree is a empty." << endl;
		return ;
	}

	Node*	tmp = Search(data);
	if (tmp)
		Delete_helper(tmp, data);
}

Node*	AVL::Search(int data)
{
	if (!this->root)
	{
		cout << "AVL-Tree is a empty." << endl;
		return nullptr;
	}

	Node*	tmp_root = this->root;
	return Search_helper(tmp_root, data);
}

void	AVL::Inorder_Traversal()
{
	if (!this->root)
	{
		cout << "AVL-Tree is a empty." << endl;
		return;
	}

	Node*	tmp_root = this->root;
	Inorder_Traversal_helper(tmp_root);
}

void	AVL::Preorder_Traversal()
{
	if (!this->root)
	{
		cout << "AVL-Tree is a empty." << endl;
		return;
	}

	Node*	tmp_root = this->root;
	Preorder_Traversal_helper(tmp_root);
}

void	AVL::Postorder_Traversal()
{
	if (!this->root)
	{
		cout << "AVL-Tree is a empty." << endl;
		return;
	}

	Node*	tmp_root = this->root;
	Postorder_Traversal_helper(tmp_root);
}

/********************/
/*		Private		*/
/********************/


Node*	AVL::Insert_hepler(Node* node, int data)
{
	if (!node)
		return new Node(data);
	
	if (data < node->data)
		node->left = Insert_hepler(node->left, data);
	else if (data > node->data)
		node->right = Insert_hepler(node->right, data);
	else
	{
		cout << "Dublicate number forbide." << endl;
		return node;
	}

	node->height = 1 + Max(Height(node->left), Height(node->right));

	int	BF = Height(node->left) - Height(node->right);

	if (BF > 1)
	{
		if (data < node->left->data)
			return Right_Rotate(node);
		else if (data > node->left->data)
		{
			node->left = Left_Rotate(node->left);
			return Right_Rotate(node);
		}
	}
	else if (BF < -1)
	{
		if (data > node->right->data)
			return Left_Rotate(node);
		else if (data < node->right->data)
		{
			node->right = Right_Rotate(node->right);
			return Left_Rotate(node);
		}
	}

	return node;
}

int	AVL::Max(int a, int b)
{
	return a > b ? a : b;
}

int	AVL::Height(Node* node)
{
	if (!node)
		return 0;
	return node->height;
}

Node*	AVL::Delete_helper(Node* node, int data)
{
	if (!node)
		return node;
	if (data < node->data)
		node->left = Delete_helper(node->left, data);
	else if (data > node->data)
		node->right = Delete_helper(node->right, data);
	else
	{
		if (!node->left || !node->right)
		{
			Node*	tmp = node->left ? node->left : node->right;

			if (!tmp)
			{
				tmp = node;
				node = nullptr;
			}
			else
				*node = *tmp;
			delete tmp;
		}
		else
		{
			Node*	min = MinNode(node->right);

			node->data = min->data;
			node->right = Delete_helper(node->right, min->data);
		}
	}

	if (!node)
		return node;

	node->height = 1 + Max(Height(node->left), Height(node->right));

	int BF = BalanceFactor(node);

	if (BF > 1)
	{
		if (BalanceFactor(node->left) >= 0)
			return Right_Rotate(node);
		else
		{
			node->left = Left_Rotate(node->left);
			return Right_Rotate(node);
		}
	}
	if (BF < -1)
	{
		if (BalanceFactor(node->right) <= 0)
			return Left_Rotate(node);
		else
		{
			node->right = Right_Rotate(node->right);
			return Left_Rotate(node);
		}
	}

	return node;
}

Node*	AVL::MinNode(Node* node)
{
	Node*	tmp = node;
	while (tmp->left)
		tmp = tmp->left;
	return tmp;
}

Node*	AVL::MaxNode(Node* node)
{
	Node*	tmp = node;
	while (tmp->right)
		tmp = tmp->right;
	return tmp;
}

int		AVL::BalanceFactor(Node* node)
{
	if (!node)
		return 0;
	return Height(node->left) - Height(node->right);
}

Node*	AVL::Search_helper(Node* node, int data)
{
	if (!node)
	{
		cout << data << " not found." << endl;
		return nullptr;
	}

	if (node->data == data)
		return node;

	if (data < node->data)
		return Search_helper(node->left, data);
	return Search_helper(node->right, data);
}

Node*	AVL::Left_Rotate(Node* x)
{
	Node*	y = x->right;
	Node*	T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = 1 + Max(Height(x->left), Height(x->right));
	y->height = 1 + Max(Height(y->left), Height(y->right));

	return y;
}

Node*	AVL::Right_Rotate(Node* x)
{
	Node*	y = x->left;
	Node*	T2 = y->right;

	y->right = x;
	x->left = T2;

	x->height = 1 + Max(Height(x->left), Height(x->right));
	y->height = 1 + Max(Height(y->left), Height(y->right));

	return y;
}

void	AVL::Inorder_Traversal_helper(Node* node)
{
	if (!node)
		return;

	Inorder_Traversal_helper(node->left);

	if (node == this->root)
		cout << "__ ROOT __" << endl;
	
	cout << "data:\t" << node->data << endl;
	cout << "height:\t" << node->height << endl << endl;

	Inorder_Traversal_helper(node->right);
}

void	AVL::Preorder_Traversal_helper(Node* node)
{
	if (!node)
		return ;

	if (node == this->root)
		cout << "__ ROOT __" << endl;
	
	cout << "data:\t" << node->data << endl;
	cout << "height:\t" << node->height << endl << endl;

	Preorder_Traversal_helper(node->left);
	Preorder_Traversal_helper(node->right);
}

void	AVL::Postorder_Traversal_helper(Node* node)
{
	if (!node)
		return ;

	Postorder_Traversal_helper(node->left);
	Postorder_Traversal_helper(node->right);
	
	if (node == this->root)
		cout << "__ ROOT __" << endl;
	
	cout << "data:\t" << node->data << endl;
	cout << "height:\t" << node->height << endl << endl;

}