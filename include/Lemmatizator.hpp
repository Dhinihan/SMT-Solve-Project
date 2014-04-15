#ifndef LEMMATIZATOR_H
#define LEMMATIZATOR_H  

//Standard Libraries
#include <map>
#include <string>
#include <fstream>
#include <iostream>

/*  Class Lemmatizator
 *  
 *  The objects of the class Lemmatizator are containers that maps 
 *  words into its lemmas
 */
class Lemmatizator
{
    private:
        typedef std::map<std::string, std::string> lemMap;
        
        /*********************ATTRIBUTES***************************/
        
        /* Attribute lemmaMap: Map of words into its lemmas. */
        lemMap lemmaMap;
        
        /* Attribute it: iterator of the lemmaMap. */
        lemMap::iterator it;
   
    public:
    
        /*********************CONSTRUCTORS*************************/
        
        /* Standard constructor: creates a empty Lemmatizator.
         */
        Lemmatizator();
        
        /* Constructor: creates a Lemmatizator feeded by a well 
         *              formated text file.
         *
         * parameter file: path to the text file
         */
        Lemmatizator(const char* file);
        
        /************************METHODS***************************/
        
        /* Method add: Add a new word and its lemma.
         *
         * parameter key  : the word to add.
         * parameter lemma: The lemma of the word.
         */
        void add(std::string key, std::string lemma);
        
        /* Method getLemma: getter for the lemma of a given word
         *
         * parameter key: the word to be lemmatizated.
         * 
         * return: the lemma of the word
         */
        std::string getLemma(std::string key);
};

#endif
