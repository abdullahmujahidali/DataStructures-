#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;

template<typename Type>
class AVLTree
{
protected:
	struct AVLNode
	{
		Type data;
		int balance;   
		AVLNode *parent;
		AVLNode *leftchild;
		AVLNode *rightchild;
	};
	static AVLNode *_Buynode()
	{
		AVLNode *p = (AVLNode*)malloc(sizeof(AVLNode));
		if (p == NULL)
		{
			exit(1);
		}
		memset(p, 0, sizeof(AVLNode));
		return p;
	}
	static void _Freenode(AVLNode *ptr)
	{
		free(ptr);
	}
	static void RotateLeft(AVLNode *&ptr)  
	{
		AVLNode *newroot = ptr->rightchild;
		newroot->parent = ptr->parent;
		ptr->rightchild = newroot->leftchild;
		if (newroot->leftchild != NULL)
		{
			newroot->leftchild->parent = ptr;
		}
		newroot->leftchild = ptr;
		ptr->parent = newroot;
		ptr = newroot;
	}
	static void RotateRight(AVLNode *&ptr) 
	{
		AVLNode *newroot = ptr->leftchild;
		newroot->parent = ptr->parent;
		ptr->leftchild = newroot->rightchild;
		if (newroot->rightchild != NULL)
		{
			newroot->rightchild->parent = ptr;
		}
		newroot->rightchild = ptr;
		ptr->parent = newroot;
		ptr = newroot;
	}
private:
	AVLNode *root;
	Type RefValue;
public:
	AVLTree(const Type &x) :root(NULL), RefValue(x){}
	~AVLTree(){}
	static void LeftBalance(AVLNode *&ptr)
	{
		AVLNode *leftsub = ptr->leftchild;
		AVLNode *rightsub = NULL;
		switch (leftsub->balance)
		{
		case 0:cout << "letfbalance" << endl; break;
		case -1:
			ptr->balance = leftsub->balance = 0;
			RotateRight(ptr);
			break;
		case 1:
			rightsub = leftsub->rightchild;
			switch (rightsub->balance)
			{
			case -1:
				leftsub->balance = 0;
				ptr->balance = 1;
				break;
			case 1:
				leftsub->balance = -1;
				ptr->balance = 0;
				break;
			case 0:
				leftsub->balance = 0;
				ptr->balance = 0;
				break;
			}
			rightsub->balance = 0;
			RotateLeft(ptr->leftchild);
			RotateRight(ptr);
			break;
		}
	}
	static void RightBalance(AVLNode *&ptr)
	{
		AVLNode *rightsub = ptr->rightchild;
		AVLNode *leftsub = NULL;
		switch (rightsub->balance)
		{
		case 0: cout << "rightbalance" << endl;
			break;
		case 1:
			ptr->balance = rightsub->balance = 0;
			RotateLeft(ptr);
			break;
		case -1:
			leftsub = rightsub->leftchild;
			switch (leftsub->balance)
			{
			case -1:
				ptr->balance = 0;
				rightsub->balance = 1;
				break;
			case 1:
				ptr->balance = -1;
				rightsub->balance = 0;
				break;
			case 0:
				ptr->balance = 0;
				rightsub->balance = 0;
				break;
			}
			leftsub->balance = 0;
			RotateRight(ptr->rightchild);
			RotateLeft(ptr);
			break;
		}
	}

	static int Max(const int &x, const int &y)
	{
		return x>y ? x : y;
	}
	static int High(AVLNode *ptr)
	{
		if (ptr == NULL)
		{
			return 0;
		}
		return (Max(High(ptr->leftchild), High(ptr->rightchild))) + 1;
	}
	static bool Insert(AVLNode *&ptr, const Type &x, AVLNode *pa)
	{
		bool res = false;
		if (ptr == NULL)
		{
			ptr = _Buynode();
			ptr->data = x;
			ptr->parent = pa;
			res = true;
		}
		else if (ptr->data >x)
		{
			Insert(ptr->leftchild, x, ptr);
			if (ptr->balance != High(ptr->rightchild) - High(ptr->leftchild))
			{
				switch (ptr->balance)
				{
				case 0:
					ptr->balance = -1;
					break;
				case 1:ptr->balance = 0;
					break;
				case -1:
					LeftBalance(ptr);
					break;
				}
			}
		}
		else if (ptr->data<x)
		{
			Insert(ptr->rightchild, x, ptr);
			if (ptr->balance != High(ptr->rightchild) - High(ptr->leftchild))
			{
				switch (ptr->balance)
				{
				case 0:
					ptr->balance = 1;
					break;
				case -1:ptr->balance = 0;
					break;
				case 1:
					RightBalance(ptr);
					break;
				}
			}
		}
		return res;
	}
	bool Insert(const Type &x)
	{
		bool res = false;
		if (x != RefValue)
		{
			res = Insert(root, x, NULL);
		}
		return res;
	}
	static bool Remove(AVLNode *&ptr, const Type &x)
	{
		bool res = false;
		if (ptr == NULL)
		{
			return res;
		}
		if (ptr->data>x)
		{
			Remove(ptr->leftchild, x);
			if (ptr->balance != High(ptr->rightchild) - High(ptr->leftchild))
			{
				switch (ptr->balance)
				{
				case 0:
					ptr->balance = 1;
					break;
				case -1:
					ptr->balance = 0;
					break;
				case 1:
					RotateLeft(ptr);
					break;
				}
			}
		}
		else if (ptr->data<x)
		{
			Remove(ptr->rightchild, x);
			if (ptr->balance != High(ptr->rightchild) - High(ptr->leftchild))
			{
				switch (ptr->balance)
				{
				case 0:
					ptr->balance = -1;
					break;
				case 1:
					ptr->balance = 0;
					break;
				case -1:
					RotateRight(ptr);
					break;
				}
			}
		}
		else if (ptr->leftchild != NULL && ptr->rightchild != NULL)
		{
			AVLNode *p = ptr->rightchild;
			while (p->leftchild != NULL)
			{
				p = p->leftchild;
			}
			ptr->data = p->data;
			res = Remove(ptr->rightchild, ptr->data);
		}
		else
		{
			AVLNode *p = ptr;
			AVLNode *pa = ptr->parent;
			AVLNode *child = ptr->leftchild != NULL ? ptr->leftchild : ptr->rightchild;

			if (child != NULL) child->parent = pa;
			if (pa == NULL)
			{
				ptr = child;
			}
			else
			{
				if (pa->leftchild == ptr)
				{
					pa->leftchild = child;
				}
				else
				{
					pa->rightchild = child;
				}
			}
			_Freenode(p);
			res = true;
		}
		return res;
	}

	bool Remove(const Type &x)
	{
		bool res = false;
		if (x != RefValue)
		{
			res = Remove(root, x);
		}
		return res;
	}
	static AVLNode*SearchVlaue(AVLNode *ptr, const Type &x)
	{
		if (ptr == = NULL || ptr->data == x)
		{
			return ptr;
		}
		if (ptr->data>x)
		{
			SearchValue(ptr->leftchild, x);
		}
		else if (ptr->data<x)
		{
			SearchValue(ptr->rightchid, x);
		}
	}
	AVLNode *&SearchValue(const Type &x)
	{
		return SearchVlaue(root, x)
	}

	static AVLNode *First(AVLNode *ptr)
	{
		while (ptr != NULL && ptr->leftchild != NULL)
		{
			ptr = ptr->leftchild;
		}
		return ptr;
	}
	static AVLNode *Next(AVLNode *ptr)
	{
		if (ptr == NULL)
		{
			return NULL;
		}
		if (ptr->rightchild != NULL)
		{
			return First(ptr->rightchild);
		}
		else
		{
			AVLNode *pa = ptr->parent;
			while (pa != NULL && pa->leftchild != ptr)
			{
				ptr = pa;
				pa = ptr->parent;
			}
			return pa;
		}
	}
	static void InOrder(AVLNode *ptr)
	{
		for (AVLNode *s = First(ptr); s != NULL; s = Next(s))
		{
			cout << s->data << " ";
		}
	}
	void _InOrder(AVLNode *ptr)
	{
		if (ptr != NULL)
		{
			_InOrder(ptr->leftchild);
			cout << ptr->data << " ";
			_InOrder(ptr->rightchild);
		}
	}
	void InOrder()
	{
		InOrder(root);
		//_InOrder(root);
		cout << endl;
	}
};

int main()
{
	int ar[] = { 11, 9, 16, 7, 10, 13, 14, 18, 15, 26 ,26,26};
	int n = sizeof(ar) / sizeof(ar[0]);
	AVLTree<int> mytree(-1);
	for (int i = 0; i<n; ++i)
	{
		mytree.Insert(ar[i]);
	}
	mytree.InOrder();
	int x;
	cout << "Enter value to remove: ";
	while (cin >> x, x != -1)
	{
		mytree.Remove(x);
		mytree.InOrder();
	}
	return 0;
}
