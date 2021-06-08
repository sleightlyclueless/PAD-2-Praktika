#include "list.h"
#include "main.h"

int main()
{
    List<int> a;            // Linked List aus ints
    bool endthis = false;   // Ende flag


    while (!endthis)
    {
        // Print user interface
        std::cout << std::endl
            << "Welcome to your linked list. You can execute the following operations:" << std::endl
            << "(1) get - get current Node" << std::endl
            << "(2) empty - check if list is empty" << std::endl
            << "(3) end - check if we reached lists end" << std::endl
            << "(4) adv - move pointer forward once" << std::endl
            << "(5) reset - pointer to first" << std::endl
            << "(6) ins - insert element at current position" << std::endl
            << "(7) del - delete element at current position" << std::endl
            << "(8) print - print full list" << std::endl
            << "(9) Quit programm" << std::endl;

        std::cout << "Please choose the operation you wish to execute: ";
        int input = get_number();   // User input
        while (input < 1 || 9 < input)
        {
            std::cout << "Please choose between the given options 1-9!" << std::endl;
            input = get_number();
        }

        int x = -1;
    	
    	switch (input)
    	{
	        case 1:
                std::cout << a.get().print() << std::endl;
	            break;

            case 2:
                std::cout << std::boolalpha;  //bool als "true" und "false" darstellen
                std::cout << a.empty() << std::endl;
                std::cout << std::noboolalpha;
                break;

            case 3:
                std::cout << std::boolalpha;  //bool als "true" und "false" darstellen
                std::cout << a.end() << std::endl;
                std::cout << std::noboolalpha;
                break;

            case 4:
                a.adv();
                break;

            case 5:
                a.reset();
                break;

            case 6:
                std::cout << "Enter number to insert: ";
                x = get_number();
                try
                {
                    a.ins(x);

                }
                catch (std::invalid_argument e)
                {
                    std::cout << "Element could not be inserted.\n";
                    system("pause");
                }
                break;

            case 7:
                try
                {
                    a.del();
                }
                catch (std::out_of_range e)
                {
                    std::cout << e.what();
                    system("pause");
                }
                break;

            case 8:
                std::cout << a.print().str();
                break;

            case 9:
                endthis = true;
                break;

            default:
                std::cout << "Invalid command.\n";
                system("pause");
                break;
    	}

    }

    return 0;
}
