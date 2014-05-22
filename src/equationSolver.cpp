//Standard Libraries
#include <iostream>
#include <string>
#include <fstream>

//Header Files
#include "../include/CVC4solver.hpp"
#include "../include/Matrix.hpp"

int main(int argc, char* argv[])
{   
    if (argc < 2)
    {
        std::cout << "I need a input file " << argc;
        return -1;
    }
    
    //Opening the input;
    std::ifstream input (argv[1]);
    
    if(!input.is_open())
    {
        std::cout << "Error while trying to open " << argv[1] << "\n";
        return -1;
    }
    
    std::string buffer;
    std::string line;
    std::string answer;
    
    //Reading the input
    while(std::getline(input, line))
    {   
        buffer.insert(buffer.size(), line);
        buffer.insert(buffer.size(), " ");
    }
    
    input.close();
    
    bool v = false;
    if(argc == 3 && argv[2][1] == 'v')
        v = true;
    
    Matrix coef(buffer);
    
    std::vector<double>& rV = coef.getVector();
    int n = coef.getN();
    int w = coef.getW();
    
    std::cout << "INEQUATION:\n\n";
    
    std::cout << rV[0] << "\n\n";
    
    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < n; j++)
        {
            std::cout << " + x[" << i+1 << "," << j+1 << "]*("<< rV[i*n + j + 1] << ")";
        }
        std::cout << "\n\n";
    }
    
    std::cout << ">= 0\n\n";
    
    std::vector<int> sol = CVC4Solver::solveInequation(rV, n, w);
    
    std::cout << "SOLUTION:\n\n"; 
    
    if(sol[0] != 0)
        for(int i = 0; i < w; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                std::cout << "x[" << i+1 << "," << j << "] = "<< sol[i*n + j] << " ";
            }
            std::cout << "\n\n";
        }
    else
        std::cout <<"There are no solutions.\n";
    
    return 1;
}
