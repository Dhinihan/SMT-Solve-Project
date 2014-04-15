//Header files
#include "Dictionary.hpp"
#include "Lemmatizator.hpp"
//The Methods are better described in the header file

Dictionary::Dictionary()
{
    lTor = new Lemmatizator("lib/lemmas.lst");
    M = 0;
}

Dictionary::Dictionary(const char* N, const char* V)
{
    std::ifstream FILEN, FILEV;
    M = 0;
    lTor = new Lemmatizator("lib/lemmas.lst");
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

Dictionary::~Dictionary()
{
    delete lTor;
}

bool Dictionary::add(std::string key, char type)
{
    key = lTor->getLemma(key);
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
    key = lTor->getLemma(key);
    if(hasKey(key))
        return words[key];
    return 'D';
}

bool Dictionary::hasKey(std::string key)
{
    key = lTor->getLemma(key);
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
