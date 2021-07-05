#pragma once

template<typename T>
class Node
{
	public:
		T data;
		long key;
		Node<T>* childLeft;
		Node<T>* childRight;
		Node<T>* parent;

		Node()
		{
			data = {};
			key = 0;
			parent = nullptr;
			childLeft = nullptr;
			childRight = nullptr;
		}

		~Node() = default;

		T print() const
		{
			return data;
		}
};