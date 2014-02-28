//Standard Libraries
#include <iostream>
#include <string>

//Header files
#include "classes/Dictionary.hpp"
 
int main()
{
    std::string input;
    /* Loading the dictionary*/
    Dictionary* dic = new Dictionary("lib/Nouns.lst", "lib/Verbs.lst");
    
    while(std::cin >> input)
    {
        /* Removing commas */
        if(input.back() == ',')
            input = input.substr(0, input.size() - 1);
        
        /* Removing punctuation */
        if (input.back() == '.' 
        ||  input.back() == '!' 
        ||  input.back() == '?') input = input.substr(0, input.size() - 1);
       
        /*Printing the symbols (V,D,N)*/
        std::cout << dic->getType(input) << " ";
    }

    delete dic;
    return 1;
}
