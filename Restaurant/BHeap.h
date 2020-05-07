#pragma once
#include "../Restaurant/Generic_DS/HNode.h"
template < typename T>
class BHeap
{
private:
	HNode<T>* root;
	static void rec_heapify(HNode<T>*& subRoot);
	static HNode<T>* rec_deepestHNode(HNode<T>*& subRoot);
	static void rec_findLastHNode(HNode<T>*& subRoot, int level, int& maxLevel, HNode<T>*& res);
	static void rec_nullParent(HNode<T>*& subRoot, HNode<T>* child);
	static void rec_deleteMax(HNode<T>*& subRoot, T& maxEntry);
	static int rec_CountHNodes(HNode<T>*& subRoot);
	static int rec_height(HNode<T>*& subRoot);
	static void rec_toArray(HNode<T>*& subRoot, int level, T*& arr, int& i);
	static void rec_insert(HNode<T>*& subRoot, double key, T data);

	static void rec_destroy_tree(HNode<T>*& subRoot);

public:
	BHeap(void);
	~BHeap(void);

	void heapify();
	bool empty() const;
	void insert(double key, T data); // not const
	bool peekFront(T& frntEntry)  const;
	void deleteMax(T& maxEntry); // not const
	int CountHNodes();
	T* toArray(int& count);

	void destroy_tree(); // not const

};

template < typename T>
BHeap<T>::BHeap(void)
{
	root = nullptr;
}
template < typename T>
BHeap<T>::~BHeap(void)
{
	destroy_tree();
}

template < typename T>
void BHeap<T>::rec_findLastHNode(HNode<T>*& subRoot, int level, int& maxLevel, HNode<T>*& res)
{
	if (subRoot != nullptr)
	{
		rec_findLastHNode(subRoot->getleft(), ++level, maxLevel, res);

		// Update level and resue 
		if (level > maxLevel)
		{
			res = subRoot;
			maxLevel = level;
		}

		rec_findLastHNode(subRoot->getright(), level, maxLevel, res);
	}
	return;
}

template < typename T>
HNode<T>* BHeap<T>::rec_deepestHNode(HNode<T>*& subRoot)
{
	HNode<T>* res;
	int maxLevel = -1;
	rec_findLastHNode(subRoot, 0, maxLevel, res);
	return res;
}

template < typename T>
void BHeap<T>::rec_heapify(HNode<T>*& subRoot)
{
	HNode<T>* larg = subRoot;
	HNode<T>* temp;
	int left, right, largest;
	if (subRoot == nullptr)
		return;
	left = (subRoot->getleft() != nullptr) ? subRoot->getleft()->getpriority() : 0;
	right = (subRoot->getright() != nullptr) ? subRoot->getright()->getpriority() : 0;

	if (left > subRoot->getpriority() && subRoot->getleft() != nullptr)
	{
		larg = subRoot->getleft();
		temp = subRoot->getright();
		subRoot->setleft(larg->getleft());
		subRoot->setright(larg->getright());

		larg->setleft(subRoot);
		larg->setright(temp);

		subRoot = larg;
	}
	if (right > subRoot->getpriority() && subRoot->getright() != nullptr)
	{
		larg = subRoot->getright();
		temp = subRoot->getleft();
		subRoot->setleft(larg->getleft());
		subRoot->setright(larg->getright());

		larg->setleft(temp);
		larg->setright(subRoot);

		subRoot = larg;
	}

	rec_heapify(subRoot->getleft());

	rec_heapify(subRoot->getright());
}

template < typename T>
void BHeap<T>::rec_nullParent(HNode<T>*& subRoot, HNode<T>* child)
{
	if (subRoot == nullptr)
		return;
	if (subRoot->getleft() == child)
		subRoot->setleft(nullptr);
	if (subRoot->getright() == child)
		subRoot->setright(nullptr);

	rec_nullParent(subRoot->getleft(), child);

	rec_nullParent(subRoot->getright(), child);
}

template < typename T>
void BHeap<T>::rec_insert(HNode<T>*& subRoot, double key, T data)
{
	if (subRoot == nullptr)
		subRoot = new HNode<T>(key, data); // this line is why we pass subRoot by reference (subRoot = something)
	else if (subRoot->getpriority() < key)
	{
		rec_insert(subRoot->getright(), key, data);
	}
	else
	{
		rec_insert(subRoot->getleft(), key, data);
	}

	rec_heapify(subRoot);
}

template < typename T>
void BHeap<T>::rec_deleteMax(HNode<T>*& subRoot, T& maxEntry)
{
	HNode<T>* lastHNode = rec_deepestHNode(subRoot);
	rec_nullParent(subRoot, lastHNode);
	lastHNode->setleft(subRoot->getleft());
	lastHNode->setright(subRoot->getright());
	maxEntry = subRoot->getdata();
	//delete subRoot;
	subRoot = lastHNode;

	rec_heapify(subRoot);
}

template<typename T>
int BHeap<T>::rec_CountHNodes(HNode<T>*& subRoot)
{
	int c = 1;             //HNode itself should be counted
	if (subRoot == nullptr) return 0; // tree has no HNodes 
	else
	{
		c += rec_CountHNodes(subRoot->getleft());
		c += rec_CountHNodes(subRoot->getright());
		return c;
	}
}

template<typename T>
inline int BHeap<T>::rec_height(HNode<T>*& subRoot)
{
	if (subRoot == nullptr)
		return 0;
	else
	{
		/* compute the height of each subtree */
		int lheight = rec_height(subRoot->getleft());
		int rheight = rec_height(subRoot->getright());

		/* use the larger one */
		if (lheight > rheight)
			return(lheight + 1);
		else return(rheight + 1);
	}
}

template<typename T>
void BHeap<T>::rec_toArray(HNode<T>*& subRoot, int level, T*& arr, int& i)
{
	if (subRoot == nullptr)
		return;
	if (level == 1)
	{
		arr[i] = subRoot->getdata();
		i++;
	}
	else if (level > 1)
	{
		rec_toArray(subRoot->getleft(), level - 1, arr, i);
		rec_toArray(subRoot->getright(), level - 1, arr, i);
	}
}

template < typename T>
void BHeap<T>::rec_destroy_tree(HNode<T>*& subRoot)
{
	if (subRoot != nullptr)
	{
		// recursive call on left
		rec_destroy_tree(subRoot->getleft());

		// recursive call on right
		rec_destroy_tree(subRoot->getright());

		delete subRoot;
		subRoot = nullptr; // this line is why we pass subRoot by reference (subRoot = something)
	}
}


template < typename T>
void BHeap<T>::heapify()
{
	rec_heapify(root);
}

template<typename T>
bool BHeap<T>::empty() const
{
	if (root == nullptr)
		return true;
	else
		return false;
}

template < typename T>
void BHeap<T>::insert(double key, T data)
{
	rec_insert(root, key, data);
}

template<typename T>
bool BHeap<T>::peekFront(T& maxEntry) const
{
	if (empty())
		return false;

	maxEntry = root->getdata();
	return true;
}

template < typename T>
void BHeap<T>::deleteMax(T& maxEntry)
{
	rec_deleteMax(root, maxEntry);
}

template<typename T>
int BHeap<T>::CountHNodes()
{
	return rec_CountHNodes(root);
}

template<typename T>
T* BHeap<T>::toArray(int& count)
{
	int size = rec_CountHNodes(root);
	count = size;
	int h = rec_height(root);
	T* arr = new T[size];
	int i = 0;
	for (int j = 1; j <= h; j++)
		rec_toArray(root, j, arr, i);
	return arr;
}

template < typename T>
void BHeap<T>::destroy_tree()
{
	rec_destroy_tree(root);
}