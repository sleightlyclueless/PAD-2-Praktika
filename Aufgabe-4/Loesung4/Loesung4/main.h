#pragma once
#include <iostream>
#include <string>

// Problem: Before cin int input like 10f3r5 resulted in 10 - break after the letter. Could lead to unwanted results.
// Therefore check and only accept digit entries.
inline int get_number() {

    // Initialize necessary vars
    std::string str;
    int a = -1;

    // Read whole input cin into string var first, because here it does not break after letters
    while (getline(std::cin, str))
    {
        // Exception if empty - request valid entry
        if (str.empty())
        {
            std::cout << "Error, you have to enter something. Please do so!" << std::endl;
            continue;
        }

        // Search if there is an unwanted char in string.
        // size_t can store up to max size of an object - if we do not find an unaccepted char it becomes -1 or npos (18446744073709551615 == -1)
        size_t const flag = str.find_first_not_of("-0123456789");

        // npos is type size_t and cant be negative therefore it takes on the value of the highest possible number. If that is the case we have an accepted integer input
        if (flag == std::string::npos)
        {
            // Success - valid int - transform to int
            a = stoi(str);
            // If we found an fitting int - exit the whole while loop - we are done here
            break;
        }

        std::cout << "Error, enter only valid int numbers. Please try again!" << std::endl;
    }

    // When we exited the while loop we found an int var. Go ahead and return that to the function call.
    return a;
}
