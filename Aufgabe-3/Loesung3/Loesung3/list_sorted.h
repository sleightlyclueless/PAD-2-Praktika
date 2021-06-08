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
        I->next = nullptr;        //Element n�chstes ist nullptr
        I->prev = end;            //Element davor ist Element[-1] vorherig
        end = I;                  //Element[-1] neu ist Element neu

        if (I->prev != nullptr)    //wenn Element vorheriges existiert bzw. nicht nullptr:
            I->prev->next = I;    //von Element vorheriges Element n�chstes ist dieses Element
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
        current = begin;  //Element aktuell zu l�schen, startet bei [0]
        Node<T>* next;  //Element n�chstes

        if (current == nullptr)    //wenn keine Elemente vorhanden: nix tun
            return;

        do
        {
            next = current->next; //Element n�chstes
            delete current;     //Element aktuell l�schen
            current = next;       //Element aktuell ist Element n�chstes
        } while (next != nullptr);  //wenn Element n�chstes existiert: weitermachen
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
        Node<T>* I = current;         //Element zu l�schen

        if (I == nullptr)
            throw std::out_of_range("Error in List<T>::del(): Can not delete element from empty list.\n");

        if (I->next != nullptr)        //wenn Element n�chstes existiert bzw. nicht nullptr:
        {
            I->next->prev = I->prev;  //Element n�chstes vorheriges ist von Element aktuell vorheriges
        }
        if (I->prev != nullptr)        //wenn Element vorheriges existiert bzw. nicht nullptr:
        {
            I->prev->next = I->next;  //Element vorheriges n�chstes ist von Element aktuell n�chstes
        }

        if (I->prev != nullptr && I->next != nullptr)        //l�sche zwischen Elementen
        {
            current = I->next;
        }
        else if (I->prev == nullptr && I->next != nullptr)   //l�sche Element[0]
        {
            begin = I->next;
            current = I->next;
        }
        else if (I->prev != nullptr && I->next == nullptr)   //l�sche Element[-1]
        {
            current = I->prev;
            end = I->prev;
        }
        else if (I->prev == nullptr && I->next == nullptr)   //l�sche Element einziges
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
        Node<T>* current_before = current;    //Element aktuell merken, sp�ter wiederherstellen
        Node<T>* I = new Node<T>;             //Speicher beantragen
        I->value = I_new;                     //Daten kopieren


        //Einf�geposition suchen
        current = begin;
        if (current != nullptr)    //wenn Element aktuell existiert bzw. Liste nicht leer:
        {
            do                  //nach Einf�geposition suchen
            {
                if (*I <= *current)
                    break;

                if (*current < *I && current->next == nullptr) //wenn Element gr��er als Element letztes:
                {
                    push_back(I);               //anh�ngen
                    if (current_before != nullptr) //nach Einf�gen wenn Element aktuell alt kein nullptr:
                        current = current_before; //Element aktuell wiederherstellen
                    return;
                }
            } while (adv() == true);
        }


        //einf�gen
        I->next = current;            //Element n�chstes ist Element aktuell alt
        if (I->next != nullptr)        //wenn Element n�chstes existiert bzw. nicht nullptr:
        {
            I->prev = I->next->prev;  //Element vorheriges ist von Element n�chstes Element vorheriges
            I->next->prev = I;        //von Element n�chstes Element vorheriges ist Element neu
        }
        else                        //wenn Element n�chstes nicht existiert bzw. nullptr:
        {
            end = I;                  //Element aktuell ist Element[-1]
            I->prev = nullptr;        //Element n�chstes existiert nur nicht wenn Element aktuell alleiniges Element
            current = I;              //daher Element vorher nullptr und Element aktuell I
        }


        if (I->prev != nullptr)        //wenn Element vorheriges existiert bzw. nicht nullptr:
        {
            I->prev->next = I;        //von Element vorheriges Element n�chstes ist dieses Element
        }
        else                        //wenn Element vorheriges nicht existiert bzw. nullptr:
        {
            begin = I;                //Element aktuell ist Element[0]
        }

        if (current_before != nullptr) //nach Einf�gen wenn Element aktuell alt kein nullptr:
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
