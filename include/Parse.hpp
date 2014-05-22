#ifndef Parse_H
#define Parse_H

#include <string>
#include <vector>

//! A Class to parse the tests file. 
/*! A Parse object transform the input into a 
 *  matrix defined by its two firsts parameters. 
 * \author Vinícius Nascimento Silva.
 * \since 22/05/14
 */
class Parse
{
    private:
        int N; /*!< number of columns */
        int W; /*!< number of rows */
        
        std::vector<double> M; /*!< The Container */
        
        /************************METHODS***************************/
        
        /* Get the first integer from a string.
         *
         * \param input the input string.
         */
        static int nextNumberInt(std::string *input);
        
        /* Method Get the first double from a string.
         *
         * \param input the input string.
         */
        static double nextNumberDouble(std::string *input);
   
    public:
    
        //! Constructor.
        /*! The input must start with two integers (N and W) 
         *  and then n*w+1 doubles. The separator are space, tab or new line.
         *
         *  \param input string with the input.
         */
        Parse(std::string input);
        
        /************************METHODS***************************/
        
        //! getter for the elements.
        /*! 
         *  \param i the line of the element.
         *  \param j the column of the element.
         *  \return  the element at (i,j)
         */        
        double get(int i, int j);
        
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
        int getW();
        
        //! getter for the matrix.
        /*!
         * 
         *  \return a vector with the lines of the Matrix stacked.
         */ 
        std::vector<double>& getVector();
        
};

#endif
