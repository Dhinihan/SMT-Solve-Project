#include <iostream>
#include <map>

class Dictionary
{
    private:
        int M;
        std::map<const char*, char> words;
        std::map<const char*, char>::iterator it;
    public:
        
        Dictionary();
        //Dictionary(const char* D, const char* N, const char* V);
        
        bool            add(const char* key, char type);
        char            getType(const char* key);
        bool            hasKey(const char* key);
        unsigned int    size();
};

int main()
{
    Dictionary dic;
    dic.add("I",  'N');
    dic.add("am", 'V');
    dic.add("a",  'D');
    dic.add("guy",'N');
    std::cout << dic.getType("guy") << "\n";
    if(dic.getType("gay") == '\0')
        std::cout << "Não tem\n";
}

Dictionary::Dictionary()
{
    M = 0;
}

bool Dictionary::add(const char* key, char type)
{
    if(!hasKey(key))
    {
        words[key] = type;
        M++;
        return true;
    }
    return false;
}

char Dictionary::getType(const char* key)
{
    if(hasKey(key))
        return words[key];
    return '\0';
}

bool Dictionary::hasKey(const char* key)
{
    it = words.find(key);
    if(it == words.end())
    {
        return false;
    }
    return true;
}

