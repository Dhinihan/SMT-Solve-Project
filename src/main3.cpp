//Standard Libraries
#include <iostream>
#include <string>
#include <fstream>

//Header Files
#include "classes/CVC.hpp"

int main(int argc, char* argv[])
{   
    if (argc < 3)
    {
        std::cout << "Error 1: " << argc;
        return -1;
    }
    
    //Opening the input;
    std::ifstream input (argv[1]);
    
    if(!input.is_open())
    {
        std::cout << "Error 2 " << argv[1] << "\n";
        return -1;
    }
    
    std::string buffer;
    std::string line;
    
    //Reading the input
    while(std::getline(input, line))
    {   
        buffer.insert(buffer.size(), line);
        buffer.insert(buffer.size(), " ");
    }
    
    input.close();
    
    //Static method that creates the CVC input file.
    CVC::createFile(buffer.c_str(), argv[2]);
    
    return 1;
}
