#pragma once
#include <string>

// template T: Node kann T value (jeder mögliche Typ (int, string, etc.) enthalten kann)
template<typename T>
class Node
{
	public:
	    T value;        // Node
	    Node<T>* next;  // Node nächstes Adresse
	    Node<T>* prev;  // Node vorherige Adresse

		// Konstruktor
	    Node()
	    {
	        next = nullptr;
	        prev = nullptr;
	    }

		// Print Funktion mit string Ausgabe
	    std::string print()
	    {
	        return std::to_string(value);
	    }
};


// Item Rückgabe für überladene Vergleichsoperatoren
template<typename T>
bool operator==(Node<T> a, Node<T> b)
{
    return a.value == b.value;
}

template<typename T>
bool operator<(Node<T> a, Node<T> b)
{
    return a.value < b.value;
}

template<typename T>
bool operator>(Node<T> a, Node<T> b)
{
    return a.value > b.value;
}

template<typename T>
bool operator<=(Node<T> a, Node<T> b)
{
    return a.value <= b.value;
}

template<typename T>
bool operator>=(Node<T> a, Node<T> b)
{
    return a.value >= b.value;
}
