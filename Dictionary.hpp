
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

