#include <iostream>
#include <Windows.h>
using namespace std;

struct Node
{
	Node* left, * right;
	int info;
};

Node* CreateTree(int nodeCount)
{
	if (nodeCount == 0)
		return nullptr;
	else
	{
		Node* newNode = new Node;

		cout << "Введіть значення вузла: ";
		cin >> newNode->info;

		int leftCount = nodeCount / 2;
		int rightCount = nodeCount - leftCount - 1;
		newNode->left = CreateTree(leftCount);
		newNode->right = CreateTree(rightCount);
		return newNode;
	}
}

void PrintTree(Node* root, int level)
{
	if (root != nullptr)
	{
		PrintTree(root->right, level + 1);
		for (int i = 1; i <= level; i++)
			cout << " ";
		cout << root->info << endl;
		PrintTree(root->left, level + 1);
	}
}

Node* rightRotation(Node* p) {
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	return q;
}
Node* leftRotation(Node* q) {
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	return p;
}
int Height(Node* root) {
	if (root == nullptr)
		return 0;
	int hL = Height(root->left);
	int hR = Height(root->right);
	return (hL > hR ? hL : hR) + 1;
}

int BFactor(Node * root)
{
	return Height(root->right) - Height(root->left);
}
Node* balanceHeight(Node* p)
{
	if (BFactor(p) == 2)
	{
		if (BFactor(p->right) < 0)
			p->right = rightRotation(p->right);
		return leftRotation(p);
	}
	if (BFactor(p) == -2)
	{
		if (BFactor(p->left) > 0)
			p->left = leftRotation(p->left);
		return rightRotation(p);
	}
	return p;
}
Node* Insert(Node* p, int value)
{
	if (!p)
	{
		p = new Node;
		p->info = value;
		p->left = nullptr;
		p->right = nullptr;
		return p;
	}
	if (value < p->info)
		p->left = Insert(p->left, value);
	else
		if (value > p->info)
			p->right = Insert(p->right, value);
	return balanceHeight(p);
}

Node* FindMax(Node* root) {
	if (root->right != nullptr)
		return FindMax(root->right);
	else
		return root;
}

Node* BinarySearchDelete(Node* root, int value)
{
	if (nullptr == root) return nullptr;
	if (root->info == value)
	{
		if (nullptr == root->left && nullptr == root->right)
		{
			delete root;
			return nullptr;
		}
		if (nullptr == root->right && root->left != nullptr)
		{
			Node* temp = root->left;
			delete root;
			return temp;
		}
		if (nullptr == root->left && root->right != nullptr)
		{
			Node* temp = root->right;
			delete root;
			return temp;
		}
		root->info = FindMax(root->left)->info;
		root->left = BinarySearchDelete(root->left, root->info);
		return root;
	}
	if (value < root->info)
	{
		root->left = BinarySearchDelete(root->left, value);
		return root;
	}
	if (value > root->info)
	{
		root->right = BinarySearchDelete(root->right, value);
		return root;
	}
	return root;
}

void DeleteTree(Node*& root, Node* node)
{
	if (node != nullptr)
	{
		DeleteTree(root, node->left);
		DeleteTree(root, node->right);
		root = BinarySearchDelete(root, node->info);
	}
}

Node* FindMin(Node* root)
{
	if (root->left != nullptr)
		return FindMin(root->left);
	else
		return root;
}

Node* deleteMin(Node* p)
{
	if (p->left == 0)
		return p->right;
	p->left = deleteMin(p->left);
	return balanceHeight(p);
}
Node* Delete(Node* p, int value)
{
	if (!p)
		return 0;
	if (value < p->info)
		p->left = Delete(p->left, value);
	else if (value > p->info)
		p->right = Delete(p->right, value);
	else
	{
		Node* q = p->left;
		Node* r = p->right;
		delete p;
		if (!r)
			return q;
		Node* min = FindMin(r);
		min->right = deleteMin(r);
		min->left = q;
		return balanceHeight(min);
	}
	return balanceHeight(p);
}

void findMax(Node* root, int &max)
{
	if (root != nullptr)
	{
		findMax(root->left, max);
		findMax(root->right, max);
		if (root->info > max) max = root->info;
	}
}

Node* Find(Node* root, int value)
{
	if (root == nullptr || value == root->info)
		return root;
	if (value < root->info)
		return Find(root->left, value);
	else
		return Find(root->right, value);
}

void PrintTreeMax(Node* root, int level, int max)
{
	if (root != nullptr)
	{
		PrintTreeMax(root->right, level + 1, max);
		for (int i = 1; i <= level; i++)
			cout << " ";
		if (root->info == max) cout << "*";
		cout << root->info << endl;
		PrintTreeMax(root->left, level + 1, max);
	}
}

int main()
{
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Node* root = nullptr;

	int choice;
	do
	{
		cout << "1 Створити бінарне дерево" << endl;
		cout << "2 Вивід бінарного дерева" << endl;
		cout << "3 Створити бінарное дерево пошуку" << endl;
		cout << "4 Добавити новий елемент" << endl;
		cout << "5 Збалансування бінарного дерева" << endl;
		cout << "6 Видалення елемента" << endl;
		cout << "7 Видалення під дерева" << endl;
		cout << "8 максимальний елемент в «постфіксному»" << endl;
		cout << "9 генерація бінарное дерево пошуку " << endl;
		cout << "choice = "; cin >> choice;

		switch (choice)
		{
		case 1:
		{
			int count = 0;
			cout << "Введіть кількість вузлів: "; cin >> count;
			root = CreateTree(count);
			break;
		}
		case 2: {
			PrintTree(root, 0);
			break;
		}
		case 3: {
			int count = 0;
			cout << "Введіть кількість вузлів: "; cin >> count;
			for (int i = 0; i < count; i++)
			{
				int info;
				cout << "Введіть значення: "; cin >> info;
				root = Insert(root, info);
			}

			break;
		}
		case 4: {
			int info;
			cout << "Введіть значення: "; cin >> info;
			root = Insert(root, info);
			break;
		}
		case 5: {
			root = balanceHeight(root);
			break;
		}
		case 6: {
			int info;
			cout << "Введіть значення елемента: "; cin >> info;
			root = BinarySearchDelete(root, info);
			break;
		}
		case 7: {
			int info;
			cout << "Введіть значення елемента: "; cin >> info;
			DeleteTree(root, Find(root, info));
			break;
		}
		case 8: {
			int max;
			findMax(root, max);
			PrintTreeMax(root, 0, max);
			break;
		}
		case 9: {
			int count = 0;
			cout << "Введіть кількість вузлів: "; cin >> count;
			for (int i = 0; i < count; i++)
			{
				root = Insert(root, rand() % 21);
			}
			break;
		}
		}
	} while (choice != 0);

	return 0;
}