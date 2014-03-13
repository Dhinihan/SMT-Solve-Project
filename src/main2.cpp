//Standard Libraries
#include <iostream>
#include <string>
#include <fstream>

//Header files
#include "classes/Matrix.hpp"
#include "classes/CVC.hpp"

int main(int argc, char* argv[])
{   
    if (argc < 3)
    {
        std::cout << "Error 1: " << argc;
        return -1;
    }
    
    std::ifstream input (argv[1]);
    
    if(!input.is_open())
    {
        std::cout << "Error 2 " << argv[1] << "\n";
        return -1;
    }
    
    std::string buffer;
    std::string line;
    
    while(std::getline(input, line))
    {   
        buffer.insert(buffer.size(), line);
        buffer.insert(buffer.size(), " ");
    }
    
    input.close();
    
    Matrix* M = new Matrix(buffer);
    
    CVC::createFile(M, argv[2]);
    
    return 1;
}
