//Standard Libraries
#include <map>
#include <string>
#include <fstream>
#include <iostream>

//Header file
#include "Dictionary.hpp"

//Just a test function
int main()
{
    Dictionary dic("Nouns.lst", "Verbs.lst");
    char c = dic.getType("man");
    std::cout << c << " ";
    c = dic.getType("be");
    std::cout << c << " ";
    c = dic.getType("woman");
    std::cout << c << " ";
    c = dic.getType("!");
    std::cout << c << "\n";
    std::cout << "Size is " << dic.size() << "\n";
}

//The Methods are better described in the header file

Dictionary::Dictionary()
{
    M = 0;
}

Dictionary::Dictionary(const char* N, const char* V)
{
    std::ifstream FILEN, FILEV;
    M = 0;
    std::string temp;
    FILEN.open(N, std::ios::in); //File with the nouns
    FILEV.open(V, std::ios::in); //File with the verbs
    
    if(FILEN)
    {
        // This loop reads the file with the nouns
        while(std::getline(FILEN, temp))
            add(temp, 'N');
    }
    else
    {
        std::cerr << "Error opening " << N << "\n";
    }
    
    if(FILEV)
    {
        // This loop reads the file with the verbs
        while(std::getline(FILEV, temp))
            add(temp, 'V');
    }
    else
    {
        std::cerr << "Error opening " << V << "\n";
    }
}

bool Dictionary::add(std::string key, char type)
{
    if(!hasKey(key))
    {
        words[key] = type;
        M++;
        return true;
    }
    return false;
}

char Dictionary::getType(std::string key)
{
    if(hasKey(key))
        return words[key];
    return 'D';
}

bool Dictionary::hasKey(std::string key)
{
    it = words.find(key);
    if(it == words.end())
    {
        return false;
    }
    return true;
}

unsigned int Dictionary::size()
{
    return M;
}
