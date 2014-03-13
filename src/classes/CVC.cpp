//Includes
#include <fstream>
#include <iostream>

//Header File
#include "Matrix.hpp"
#include "CVC.hpp"

void CVC::createFile(Matrix* M, const char* fileName)
{
    std::ofstream file(fileName);
    
    if(file)
    {
        // Getting the parameters
        int N = M->getColumnSize();
        int W = M->getRowSize();
        
        // Creating the variables.
        file << "x0";
        for(int i = 1; i < N; i++)
            file << " ,x" << i;
        file << ": REAL;\n";
        file << "ASSERT x0 = 1;\n";

        // Restricting the values for the x's
        for(int i = 1; i < N; i++)
            file << "ASSERT x" << i << " = 0 OR x" << i << " = 1;\n";
            
        // Printing the inequations
        for(int i = 0; i < W; i++)
        {
            file << "ASSERT ";
            for(int j = 0; j < N-1; j++)
            {
                file << M->get(i,j) << "*";
                file << "x" << j << " + ";
            }
            
            file << M->get(i,N-1) << "*";
            file << "x" << (N-1);
            file << " > 0;\n";
        }
        
        // Commands to the CVC do the work.
        file << "CHECKSAT;\n";
        
        file << "COUNTERMODEL;\n";
        
        return;
   }
   
       std::cout << "Error creating the CVC file\n";
       return;
}
