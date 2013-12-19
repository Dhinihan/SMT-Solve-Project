//Standard Libraries
#include <iostream>
#include <string>

//Header files
#include "classes/Dictionary.hpp"
 
int main()
{
    std::string input;
    Dictionary* dic = new Dictionary("lib/Nouns.lst", "lib/Verbs.lst");
    
    while(std::cin >> input)
    {
        bool end = false;
        
        if(input.back() == ',')
            input = input.substr(0, input.size() - 1);
        
        if (input.back() == '.' 
        ||  input.back() == '!' 
        ||  input.back() == '?')
        {
            end = true;
            input = input.substr(0, input.size() - 1);
        }
        
        std::cout << dic->getType(input) << " ";
        
        if(end) std::cout << "\n";
    }

    delete dic;
    return 1;
}
