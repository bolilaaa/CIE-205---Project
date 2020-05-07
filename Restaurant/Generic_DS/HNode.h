#pragma once

template < typename T>
class HNode
{
private:
	double priority;
	T data;
	HNode<T>* left;
	HNode<T>* right;
public:
	HNode(double key, T val);
	void setpriority(double p);
	double getpriority();
	void setdata(T d);
	T getdata();
	void setright(HNode<T>* p);
	HNode<T>*& getright();

	void setleft(HNode<T>* p);
	HNode<T>*& getleft();
};

template < typename T>
HNode<T>::HNode(double key, T val)
{
	priority = key;
	data = val;
	left = right = nullptr;
}
template < typename T>
void HNode<T>::setpriority(double p)
{
	priority = p;
}
template < typename T>
double HNode<T>::getpriority()
{
	return priority;
}
template < typename T>
void HNode<T>::setdata(T d)
{
	data = d;
}
template < typename T>
T HNode<T>::getdata()
{
	return data;
}
template < typename T>
void HNode<T>::setleft(HNode<T>* p)
{
	left = p;
}
template < typename T>
HNode<T>*& HNode<T>::getleft()
{
	return left;
}
template < typename T>
void HNode<T>::setright(HNode<T>* p)
{
	right = p;
}
template < typename T>
HNode<T>*& HNode<T>::getright()
{
	return right;
}