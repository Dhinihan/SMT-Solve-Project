#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <vector>

/*  Class Matrix
 *  
 *  Container for the constants of the problem.
 */
class Matrix
{
    private:
        /*********************ATTRIBUTES***************************/
        
        /* Attribute N: number of coefficients on each equation. */
        /* Attribute W: number of equations. */
        int N, W;
        
        /* Attribute M: Vector with the coefficients. */
        std::vector<double> *M;
        
        /************************METHODS***************************/
        
        /* Method nextNumberInt: get an integer from a string.
         *
         * parameter input: the string.
         */
        static int nextNumberInt(std::string *input);
        
        /* Method nextNumberDouble: get a double from a string.
         *
         * parameter input: the string.
         */
        static double nextNumberDouble(std::string *input);
   
    public:
    
        /*********************CONSTRUCTORS*************************/
        
        /* Constructor: creates a cotainer of coefficients feeded by a 
         *              well formated string. 
         *
         * parameter input: the string
         */
        Matrix(std::string input);
        
        /************************METHODS***************************/
        
        /* Method get: get a double from the Matrix.
         *
         * parameter i: the row of the number
         * parameter j: the column of the number
         *
         * return: the element in the given position
         */
        double get(int i, int j);
        
        /* Method getRowSize
         * 
         * return: The number of equations
         */
        int getRowSize();
        
        /* Method getColumnSize
         * 
         * return: The number of coefficients on each equation
         */
        int getColumnSize();
        
};

#endif
