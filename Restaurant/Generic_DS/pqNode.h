
#ifndef __PQ_NODE_H_
#define __PQ_NODE_H_

template < typename T>
class pqNode
{
private:
	T item; // A data item
	pqNode<T>* next; // Pointer to next node
	double priority;
public:
	pqNode();
	pqNode(const T& r_Item);	//passing by const ref.
	pqNode(const T& r_Item, pqNode<T>* nextNodePtr);
	void setItem(const T& r_Item);
	void setNext(pqNode<T>* nextNodePtr);
	T getItem() const;
	pqNode<T>* getNext() const;
}; // end Node


template < typename T>
pqNode<T>::pqNode()
{
	next = nullptr;
}

template < typename T>
pqNode<T>::pqNode(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename T>
pqNode<T>::pqNode(const T& r_Item, pqNode<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void pqNode<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void pqNode<T>::setNext(pqNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T pqNode<T>::getItem() const
{
	return item;
}

template < typename T>
pqNode<T>* pqNode<T>::getNext() const
{
	return next;
}

#endif