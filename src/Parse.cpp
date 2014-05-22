//Includes
#include <iostream> 

//Header File
#include "../include/Parse.hpp"

Parse::Parse(std::string input)
{
    N = nextNumberInt(&input);
    W = nextNumberInt(&input);
    
    if (N < 1 )
    {
        std::cout << "The N value is invalid\n";
    }
    
    if (W < 1 )
    {
        std::cout << "The W value is invalid\n";
    }
        
    for(int i = 0; i < N*W+1; i++)
    {
        M.push_back(nextNumberDouble(&input));
    }
}

double Parse::get(int i, int j)
{
    return M.at(i*N + j);
}

int Parse::getN()
{
    return N;
}

int Parse::getW()
{
    return W;
}

std::vector<double>& Parse::getVector()
{
    return M;
}

int Parse::nextNumberInt(std::string* input)
{
    int answer = atoi(input->c_str());

    while(input->at(0) == ' ')
        input->erase(0, 1);
    while(input->at(0) != ' ')
        input->erase(0, 1);
        
    return answer;
}

double Parse::nextNumberDouble(std::string* input)
{
    double answer = atof(input->c_str());

    while(input->at(0) == ' ')
        input->erase(0, 1);
    while(input->at(0) != ' ')
        input->erase(0, 1);
        
    return answer;
}
