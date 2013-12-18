#include <map>
#include <string>
#include <fstream>
#include <iostream>

#include "Dictionary.hpp"

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

Dictionary::Dictionary()
{
    M = 0;
}

Dictionary::Dictionary(const char* N, const char* V)
{
    std::ifstream FILEN, FILEV;
    M = 0;
    std::string temp;
    FILEN.open(N, std::ios::in);
    FILEV.open(V, std::ios::in);
    
    if(FILEN)
    {
        while(std::getline(FILEN, temp))
            add(temp, 'N');
    }
    else
    {
        std::cerr << "Error opening " << N << "\n";
    }
    
    if(FILEV)
    {
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
