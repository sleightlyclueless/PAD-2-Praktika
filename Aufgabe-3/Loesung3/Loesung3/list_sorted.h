#pragma once
#include "node.h"
#include <iostream>

template<typename T>
class List_sorted
{
private:
    Node<T>* begin;
    Node<T>* current;
    Node<T>* end;

    void push_back(Node<T>* I)
    {
        I->next = nullptr;        //Element nächstes ist nullptr
        I->prev = end;            //Element davor ist Element[-1] vorherig
        end = I;                  //Element[-1] neu ist Element neu

        if (I->prev != nullptr)    //wenn Element vorheriges existiert bzw. nicht nullptr:
            I->prev->next = I;    //von Element vorheriges Element nächstes ist dieses Element
        else                    //wenn Element vorheriges nicht existiert bzw. nullptr:
            begin = I;            //Element[0] ist Element aktuell
        if (current == nullptr)    //wenn Element aktuell nullptr bzw Liste vorher leer:
            current = I;          //Element aktuell ist Element neu
    }

public:
    List_sorted()
    {
        begin = nullptr;
        current = nullptr;
        end = nullptr;
    }
    ~List_sorted()
    {
        current = begin;  //Element aktuell zu löschen, startet bei [0]
        Node<T>* next;  //Element nächstes

        if (current == nullptr)    //wenn keine Elemente vorhanden: nix tun
            return;

        do
        {
            next = current->next; //Element nächstes
            delete current;     //Element aktuell löschen
            current = next;       //Element aktuell ist Element nächstes
        } while (next != nullptr);  //wenn Element nächstes existiert: weitermachen
    }

    bool adv()
    {
        if (current != nullptr && current->next != nullptr)
        {
            current = current->next;
            return true;
        }
        else return false;
    }

    void del()
    {
        Node<T>* I = current;         //Element zu löschen

        if (I == nullptr)
            throw std::out_of_range("Error in List<T>::del(): Can not delete element from empty list.\n");

        if (I->next != nullptr)        //wenn Element nächstes existiert bzw. nicht nullptr:
        {
            I->next->prev = I->prev;  //Element nächstes vorheriges ist von Element aktuell vorheriges
        }
        if (I->prev != nullptr)        //wenn Element vorheriges existiert bzw. nicht nullptr:
        {
            I->prev->next = I->next;  //Element vorheriges nächstes ist von Element aktuell nächstes
        }

        if (I->prev != nullptr && I->next != nullptr)        //lösche zwischen Elementen
        {
            current = I->next;
        }
        else if (I->prev == nullptr && I->next != nullptr)   //lösche Element[0]
        {
            begin = I->next;
            current = I->next;
        }
        else if (I->prev != nullptr && I->next == nullptr)   //lösche Element[-1]
        {
            current = I->prev;
            end = I->prev;
        }
        else if (I->prev == nullptr && I->next == nullptr)   //lösche Element einziges
        {
            begin = nullptr;
            current = nullptr;
            end = nullptr;
        }

        delete I;   //Speicher freigeben
    }

    bool empty()
    {
        return current == nullptr;    //wenn Zeiger aktuell nullptr: ja, leer
    }

    T& get()
    {
        if (current != nullptr)
            return current->value;
        else throw std::out_of_range("Error in List<T>::get(): Can not get element from emtpy list.\n");
    }

    void ins(const T& I_new)
    {
        Node<T>* current_before = current;    //Element aktuell merken, später wiederherstellen
        Node<T>* I = new Node<T>;             //Speicher beantragen
        I->value = I_new;                     //Daten kopieren


        //Einfügeposition suchen
        current = begin;
        if (current != nullptr)    //wenn Element aktuell existiert bzw. Liste nicht leer:
        {
            do                  //nach Einfügeposition suchen
            {
                if (*I <= *current)
                    break;

                if (*current < *I && current->next == nullptr) //wenn Element größer als Element letztes:
                {
                    push_back(I);               //anhängen
                    if (current_before != nullptr) //nach Einfügen wenn Element aktuell alt kein nullptr:
                        current = current_before; //Element aktuell wiederherstellen
                    return;
                }
            } while (adv() == true);
        }


        //einfügen
        I->next = current;            //Element nächstes ist Element aktuell alt
        if (I->next != nullptr)        //wenn Element nächstes existiert bzw. nicht nullptr:
        {
            I->prev = I->next->prev;  //Element vorheriges ist von Element nächstes Element vorheriges
            I->next->prev = I;        //von Element nächstes Element vorheriges ist Element neu
        }
        else                        //wenn Element nächstes nicht existiert bzw. nullptr:
        {
            end = I;                  //Element aktuell ist Element[-1]
            I->prev = nullptr;        //Element nächstes existiert nur nicht wenn Element aktuell alleiniges Element
            current = I;              //daher Element vorher nullptr und Element aktuell I
        }


        if (I->prev != nullptr)        //wenn Element vorheriges existiert bzw. nicht nullptr:
        {
            I->prev->next = I;        //von Element vorheriges Element nächstes ist dieses Element
        }
        else                        //wenn Element vorheriges nicht existiert bzw. nullptr:
        {
            begin = I;                //Element aktuell ist Element[0]
        }

        if (current_before != nullptr) //nach Einfügen wenn Element aktuell alt kein nullptr:
            current = current_before; //Element aktuell wiederherstellen
    }

    std::string print()
    {
        std::string display;                //Ausgabe
        Node<T>* current_before = current;    //Element aktuell vorher merken

        current = begin;                      //Element aktuell auf Element[0] setzen
        if (current == nullptr)                //wenn Liste leer:
            return "-\n";

        int i = 0;
        do                                                      //Elemente alle durch
        {
            display += std::to_string(i) + ": " + current->print();   //drucken

            if (current == current_before)                         //wenn Element aktuell:
            {
                display += " <-";                                 //markieren
            }

            display += "\n";
            ++i;
        } while (adv() == true);

        current = current_before;     //Element aktuell wiederherstellen
        return display;
    }

    void reset()
    {
        current = begin;
    }

    bool ret()
    {
        if (current != nullptr && current->prev != nullptr)
        {
            current = current->prev;
            return true;
        }
        else return false;
    }
};
