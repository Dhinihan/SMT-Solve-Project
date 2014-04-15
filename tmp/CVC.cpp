//Includes
#include <fstream>
#include <iostream>
#include <string>

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
        {
            file << "ASSERT x" << i << " = 0 "; 
            file << "OR x" << i << " = 1;\n";
        }   
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

void CVC::createFile(const char* input, const char* fileName)       
{
    //Opening Files
    std::ofstream file(fileName);
    std::ifstream model("lib/model2.txt");
    std::string line;
    
    if(!file.is_open() || !model.is_open())
    {
        std::cout << "Error opening file " << fileName << "\n";
        return;
    }
    
    // Copying the model to the output file  
    while(std::getline(model, line))
        file << line << "\n";

    model.close();    
        
        
    // Filling the boolean array of types    
    char c = input[0];
    int size = 0;
    for(int i = 0; c = input[i], c != '\0'; i++)
    {
        switch (c)
        {
            case 'v':
            case 'V':
                file << "ASSERT v(" << size++ << ");\n"; break;
            case 'n':
            case 'N':
                file << "ASSERT n(" << size++ << ");\n"; break;
            case 'd':
            case 'D':
                file << "ASSERT d(" << size++ << ");\n"; break;
        }
    }
    
    
    // Writing the summation of distances.
    file << "\nASSERT dVN = ";
    
    for(int i = 0; i < size*size -1; i++)
    {
        file << "dist_vn(" << i/size << ", " << i%size << ") + ";
    }
    file << "dist_vn(" << size - 1 << ", " << size - 1  << ");\n";
    
    file << "\nASSERT dND = ";
    
    for(int i = 0; i < size*size -1; i++)
    {
        file << "dist_nd(" << i/size << ", " << i%size << ") + ";
    }
    file << "dist_nd(" << size - 1 << ", " << size - 1  << ");\n";
    
    file << "\nASSERT dDV = ";
    
    for(int i = 0; i < size*size -1; i++)
    {
        file << "dist_dv(" << i/size << ", " << i%size << ") + ";
    }
    file << "dist_dv(" << size - 1 << ", " << size - 1  << ");\n";
    
    //Finishing the file. 
    file << "CHECKSAT;\n";
    file << "COUNTERMODEL;\n";
    
    file.close();
}
