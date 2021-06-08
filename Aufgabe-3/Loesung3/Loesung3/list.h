#pragma once
#include "node.h"
#include <sstream>

template<typename T>
class List
{
	private:
	    Node<T>* first;						// Zeiger auf Startelement
	    Node<T>* current;					// Zeiger auf Current Element
	    Node<T>* last;						// Zeiger auf Letztes Element

	public:
		// Konstruktor
	    List()
	    {
	        first = nullptr;
	        current = nullptr;
	        last = nullptr;
	    }

		// Spezifischer Destruktor, um Pointer zu l�schen und Speicher freizugeben
	    ~List()
	    {
	        current = first;				// Beginn ganz vorne
			Node<T>* next = current;

	    	while (next != nullptr)
	    	{
				next = current->next;		// N�chstes Element
				delete current;				// Aktuelles Element l�schen
				current = next;				// Aktuelles = n�chstes Element
	    	}
	    }

		// Linked List - Funktionen
		Node<T> get();						// liefert aktuelles Element von Positionszeiger
		bool empty();					// liefert, ob Liste leer ist (ob alles = nullptr)
		bool end();						// liefert, ob Listenende erreicht ist
		bool adv();						// Positionszeiger vorr�cken
		void reset() { current = first; } // Positionszeiger auf Anfang setzen
		void ins(const T& I_new);		// Am Positionszeiger neues Element hinzuf�gen
		void del();						// Positionszeiger Element l�schen


		// General Functions
	    std::stringstream print();			// Ausgabe gesamter Liste
};


template<typename T>
Node<T> List<T>::get()						// liefert aktuelles Element von Positionszeiger
{
	{
		if (current != nullptr)
			return *current;

		// TODO return nullptr;					// nullptr R�ckgabe falls kein Element vorhanden
	}
}

template<typename T>
bool List<T>::empty()					// liefert, ob Liste leer ist (ob alles = nullptr)
{
	return current == nullptr && first == nullptr && last == nullptr;			
}

template<typename T>
bool List<T>::end()						// liefert, ob Listenende erreicht ist
{
	return current == last;
}

template<typename T>
bool List<T>::adv()						// Positionszeiger vorr�cken
{
	if (current != nullptr && current->next != nullptr)
	{
		current = current->next;
		return true;
	}
	return false;
}


template<typename T>
void List<T>::ins(const T& I_new)	// Am Positionszeiger neues Element hinzuf�gen
{
	Node<T>* I = new Node<T>;		// Am Heap neue Node erstellen
	I->value = I_new;				// Daten in Node kopieren

	I->next = current;				// Aktuelles Element 1 weiter schieben
	current = I;					// Node neu auf freien Zeigerplatz hinzuf�gen

	
	if (I->next != nullptr)			// N�chstes Element+ bearneiten
	{
		I->prev = I->next->prev;	// Zeiger auf vorheriges Element �bernehmen
		I->next->prev = I;			// Von n�chstem Element ist dieses der Vorg�nger
	}
	else
	{
		last = I;					// Kein Next = last element
		I->prev = nullptr;			// Nach weiterschieben kein next Element = prev nullptr
	}


	if (I->prev != nullptr)			// Vorheriges Element bearbeiten
	{
		I->prev->next = I;			// Von Vorherigem Element ist dieses der Nachfolger
	}
	else
	{
		first = I;					// Nach weiterschieben kein vorheriges Element = first
	}
}


template<typename T>
void List<T>::del()					// Positionszeiger Element l�schen
{
	Node<T>* I = current;			// Zu l�schende Node laden

	if (I == nullptr)
		throw std::out_of_range("Error in List<T>::del(): Can not delete element from empty list.\n");

	// Zeiger anpassen
	if (I->next != nullptr)			// N�chstes Element anpassen
	{
		I->next->prev = I->prev;	// N�chstes Element Vorg�nger = Vorg�nger von current
	}
	if (I->prev != nullptr)			// Vorheriges Element anpassen
	{
		I->prev->next = I->next;	// Vorheriges Element N�chster = N�chster von current
	}

	if (I->prev != nullptr && I->next != nullptr)        // L�sche zwischen Elementen
	{
		current = I->next;
	}
	else if (I->prev == nullptr && I->next != nullptr)   // L�sche erstes Element
	{
		first = I->next;
		current = I->next;
	}
	else if (I->prev != nullptr && I->next == nullptr)   // L�sche letztes Element
	{
		current = I->prev;
		last = I->prev;
	}
	else if (I->prev == nullptr && I->next == nullptr)   // Sonderfall: L�sche einziges
	{
		first = nullptr;
		current = nullptr;
		last = nullptr;
	}

	delete I;   // Element l�schen
}



template<typename T>
std::stringstream List<T>::print() // TODO: Gibt current element noch nicht aus?
{
	std::stringstream str;						// Ausgabestringstream
	Node<T>* current_before = current;			// Element aktuell merken f�r Ende

	current = first;							// Zeiger auf Element[0] setzen
	if (current == nullptr) {					// Wenn Liste leer:
		str << "List empty!" << std::endl;
		return str;
	}

	int i = 0;
	while (adv() == true)
	{
		if (current == current_before)
			str << "+ ";
		else
			str << "-";
		
		str << std::to_string(i) << ": " << current->print() << std::endl;

		i++;
	}

	current = current_before;					// Element aktuell wiederherstellen
	return str;
}