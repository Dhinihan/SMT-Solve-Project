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
        int N;
        int W;
        
        /* Attribute M: Vector with the coefficients. */
        std::vector<double> M;
        
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
        
        
        double get(int i, int j);
        int getSize();
        
        int getN();
        int getW();
        std::vector<double>& getVector();
        
};

#endif
