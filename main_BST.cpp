#include <cstdlib>
#include <iostream>


typedef struct node {
	int key;
	struct node *right;
	struct node *left;
} _Node;

_Node * newNode(int key)
{
	_Node * _new = (_Node *) malloc(sizeof(_Node));
	_new->key = key;
	_new->right = NULL;
	_new->left = NULL;
	return (_new);
}
// Searching
_Node* searchRecursicve(_Node* &root, int key)
{
	if (root->key == key || !root)
		return root;
	if (key < root->key)
		return (searchRecursicve(root->left, key));
	else
		return (searchRecursicve(root->right, key));
}

_Node* searchIterative(_Node* root, int key)
{
	_Node * x = root;
	while (x && x->key != key)
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return (x);
}

/* Insertion of the given node _new into the BST tree roo t*/
void insertNode(_Node * &root, _Node *&_new)
{
	if (searchIterative(root, _new->key))
		return ;
	_Node *y = NULL;
	_Node *x = root;
	while (x != NULL)
	{
		y = x;
		if (_new->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	if (!y)
		root = _new;
	else if (_new->key < y->key)
		y->left = _new;
	else
		y->right = _new;
}

/* Getting the Maximun of the given node */
_Node *treeMax(_Node *x)
{
	while(x->right)
		x = x->right;
	return (x);
}

/* Getting the minimun of the given node */
_Node *treeMin(_Node *x)
{
	while(x->left)
		x = x->left;
	return (x);
}

/* The findParent function used to find the parent of the given node */
void findParent(_Node * &root, _Node * &_node, _Node * &parent)
{
	if (!searchIterative(root, _node->key) || root == _node)
		return ;
	parent = root;
	if (parent->left == _node || parent->right == _node)
		return ;
	if (parent->key > _node->key)
		findParent(parent->left, _node, parent);
	if (parent->key < _node->key)
		findParent(parent->right, _node, parent);
}

/* treeSuccessor used to determine the successor of given node (The smallest node in node in Right subtree) */
_Node * treeSuccessor(_Node *root,_Node * x)
{
	if (x->right)
		return (treeMin(x->right));
	_Node * xparent = nullptr;
	findParent(root, x, xparent);
	_Node *y = xparent;
	_Node *yparent = nullptr;
	findParent(root, y, yparent);
	while(y != nullptr && x == y->right)
	{
		x = y;
		y = yparent;
	}
	return (y);
}

/* Replacing the node1 with the node2 */
void replaceNodes(_Node * &root, _Node * &_node1, _Node * &_node2)
{
	// get the parents
	_Node *parent1 = nullptr;
	findParent(root, _node1, parent1);
	if (parent1 == nullptr)
		root = _node2;
	else if (_node1 == parent1->left)
		parent1->left = _node2;
	else
		parent1->right = _node2;
}

void deleteNode(_Node* &root, _Node *&_node)
{
	if (!searchIterative(root, _node->key) || (!root))
		return ;
	if (!(_node->left))
		replaceNodes(root, _node, _node->right);
	else if (!(_node->right))
		replaceNodes(root, _node, _node->left);
	else
	{
		_Node * successor = treeSuccessor(root, _node);
		_Node * succPar = nullptr;
		findParent(root, successor, succPar);
		if (succPar != _node)
		{
			replaceNodes(root, successor, successor->right);
			successor->right = _node->right;
			_Node *succRP = nullptr;
			findParent(root, successor->right, succRP);
			succRP = successor;
		}
		replaceNodes(root, _node, successor);
		successor->left = _node->left;
		_Node *succLP = nullptr;
		findParent(root, successor->left, succLP);
		succLP = successor;
	}
	delete _node;
}


int main()
{
	_Node *root = nullptr;
	_Node *x[10];
	x[0] = newNode(49);
	x[1] = newNode(51);
	x[2] = newNode(29);
	x[3] = newNode(42);
	x[4] = newNode(5);
	x[5] = newNode(37);
	x[6] = newNode(95);
	x[7] = newNode(11);
	x[8] = newNode(72);
	x[9] = newNode(99);
	for (size_t i = 0; i < 10; i++)
		insertNode(root, x[i]);
		
	for (size_t i = 0; i < 10; i++)
		deleteNode(root, x[i]);
		 

	std::cout << "_____Root_____" << root << std::endl;
	_Node *srIter = searchIterative(root, x[0]->key);
	if (srIter)
		std::cout << " ____Search___ " << srIter->key << " | " << srIter->left << " | " << srIter->right << std::endl;
	else
		std::cout << " ____Node not found ____" << std::endl;
	// std::cout << " ____New______ " << x->key << " | " << x->left << " | " << x->right << std::endl;
	// insertNode(&root, x);
	// std::cout << " ____Root_____ " << root->key << " | " << root->left << " | " << root->right << std::endl;
	// _Node *x1 = newNode(5);
	// insertNode(&root, x1);
	// std::cout << " ____Root_____ " << root->key << " | " << root->left << " | " << root->right << std::endl;
	// _Node *x2 = newNode(20);
	// insertNode(&root, x2);
	// std::cout << " ____Root_____ " << root->key << " | " << root->left << " | " << root->right << std::endl;
	// _Node *x3 = newNode(15);
	// insertNode(&root, x3);
	// std::cout << " ____Root_____ " << root->key << " | " << root->left << " | " << root->right << std::endl;
	// _Node *sr = searchRecursicve(root, x1->key);
	// std::cout << " ____Search___ " << sr->key << " | " << sr->left << " | " << sr->right << std::endl;
	
}