/*  Class Dictionary
 *  
 *  The objects of the Dictionary class are containers that maps
 *  words into types (Nouns, Verbs, Determinants).
 *
 */
class Dictionary
{
    private:
        
        /*********************ATTRIBUTES***************************/
        
        /* Attribute M: Number of words in the dictionary. */
        unsigned int M;
         
        /* Attribute words: Map of words into types. */
        std::map<std::string, char> words;
        
        /* Attribute it: iterator of the map words. */
        std::map<std::string, char>::iterator it;
    public:
        
        /*********************CONSTRUCTORS*************************/
        
        /* Standard constructor: creates a empty dictionary.
         */
        Dictionary();
        
        /* Constructor: creates a dictionary from text files.
         *
         * parameter N: path to the file with the nouns
         * parameter V: path to the file with the verbs
         */
        Dictionary(const char* N, const char* V);
        
        /************************METHODS***************************/
        
        /* Method add: Add a new word and its type into the
         *             dictionary.
         *
         * parameter key : the word to add.
         * parameter type: The type of the word.
         * 
         * return: true if succeeded, false otherwise
         */
        bool            add(std::string key, char type);

        /* Method getType: getter for the type of a given word
         *
         * parameter key: the word to be typed.
         * 
         * return: the type of the word
         */
        char            getType(std::string key);
        
         /* Method hasKey: Check if the word is already in the
         *                dictionary
         *
         * parameter key: the word to check.
         * 
         * return: true if the word is in the dictionary, false
         *         otherwise.
         */
        bool            hasKey(std::string key);
        
        /* Method size: Getter for the size of the dictionary.
         *
         * return: The size of the dictionary.
         */
        unsigned int    size();
};

