#include <fstream>
#include <iostream>
#include <map>
#include <string>

class Dictionary
{
    private:
        int M;
        std::map<std::string, char> words;
        std::map<std::string, char>::iterator it;
    public:
        
        Dictionary();
        Dictionary(const char* N, const char* V);
        
        bool            add(std::string key, char type);
        char            getType(std::string key);
        bool            hasKey(std::string key);
        unsigned int    size();
};

int main()
{
    Dictionary dic("Nouns.lst", "Verbs.lst");
    char c = dic.getType("man");
    std::cout << c << " ";
    c = dic.getType("be");
    std::cout << c << " ";
    c = dic.getType("cool");
    std::cout << c << " ";
    c = dic.getType("!");
    std::cout << c << "\n";
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

