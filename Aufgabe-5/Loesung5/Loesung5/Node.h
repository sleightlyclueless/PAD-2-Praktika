#pragma once

template<typename T>
class Node
{
	public:
		T data;
		double key;
		Node<T>* childLeft;
		Node<T>* childRight;
		Node<T>* parent;

		Node()
		{
			data = {};
			key = -1;
			childLeft = nullptr;
			childRight = nullptr;
			parent = nullptr;
		}

		~Node() = default;

		T print() const
		{
			return data;
		}
};