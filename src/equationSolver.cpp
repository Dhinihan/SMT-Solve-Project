//Standard Libraries
#include <iostream>
#include <string>
#include <fstream>

//Header Files
#include "../include/Solver.hpp"

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
    
    //Static method that creates the CVC input file.
    answer = Solver::find_x(buffer, v);
    
    return 1;
}