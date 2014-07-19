#ifndef Parser_H
#define Parser_H

#include <string>
#include <vector>

using namespace std;

//! A Class to parse the tests file. 
/*! A Parser object transform the input into a 
 *  matrix defined by its two firsts parameters. 
 * \author Vinícius Nascimento Silva.
 * \since 22/05/14
 */
class Parser
{
    private:
        int N; /*!< number of columns */
        
        vector<double> probs; /*!< The Container */
        
        vector<vector<int>> clauses; /*!< The Container */
        
        /************************METHODS***************************/
        
        /* Get the first integer from a string.
         *
         * \param input the input string.
         */
        int nextNumberInt(string *input);
        
        /* Method Get the first double from a string.
         *
         * \param input the input string.
         */
        double nextNumberDouble(string *input);
        
        char nextChar(string *input);
        
        bool isComment(string* input);
   
    public:
    
        //! Constructor.
        /*! The input must start with two integers (N and W) 
         *  and then n*w+1 doubles. The separator are space, tab or 
         *  new line.
         *
         *  \param input string with the input.
         */
        Parser(string input);
        
        Parser(char* inputPath);
        
        //! getter for the size of the lines.
        /*!
         * 
         * \return the size of the lines.
         */
        int getN();
        
        //! getter for the size of the columns.
        /*!
         * 
         * \return the size of the columns.
         */
        vector<double>& getProbs();
        
        //! getter for the matrix.
        /*!
         * 
         *  \return a vector with the lines of the Matrix stacked.
         */ 
        vector<vector<int>>& getClauses();
        
};

#endif
