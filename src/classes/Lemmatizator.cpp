//Standard Libraries
#include <map>
#include <string>
#include <fstream>
#include <iostream>

//Header File
#include "Lemmatizator.hpp"

//Just a test function
main()
{
    Lemmatizator lem("lemmas.lst");
    std::cout << lem.getLemma("are") << "\n";
    return 0;
}

//The Methods are better described in the header file

Lemmatizator::Lemmatizator(const char* file)
{
    std::ifstream FILE;
    std::string temp;
    std::string actLemma;
    
    FILE.open(file, std::ios::in);
    if(FILE)
    {
        while(std::getline(FILE, temp))
        {
            // The words without the '-' prefix, are lemmas. 
            if(temp[0] != '-')
                actLemma = temp;
            else
                temp = temp.substr(1);
            add(temp, actLemma);
        }
    }
    else std::cerr << "Error opening " << file << "\n";
}

void Lemmatizator::add(std::string key, std::string lemma)
{
    lemmaMap[key] = lemma;
}

std::string Lemmatizator::getLemma(std::string key)
{
    it = lemmaMap.find(key);
    if(it == lemmaMap.end())
    {
        return key;
    }
    return lemmaMap[key];
}
