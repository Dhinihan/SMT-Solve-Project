#include <map>
#include <string>
#include <fstream>
#include <iostream>

typedef std::map<std::string, std::string> lemMap;

class Lemmatizator
{
    private:
        lemMap lemmaMap;
        lemMap::iterator it;
    public:
        Lemmatizator();
        Lemmatizator(const char* file);
        
        void add(std::string key, std::string lemma);
        std::string getLemma(std::string key);
};

main()
{
    Lemmatizator lem("lemmas.lst");
    std::cout << lem.getLemma("are") << "\n";
    return 0;
}

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
            if(temp[0] != '-')
                actLemma = temp;
            else
                temp = temp.substr(1);
            
            std::cout << actLemma << " -> " << temp << "\n";
            
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
