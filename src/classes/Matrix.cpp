//Includes
#include <iostream> 

//Header File
#include "Matrix.hpp"

Matrix::Matrix(std::string input)
{
    M = new std::vector<double>;
    
    N = nextNumberInt(&input);;
    if (N < 1 )
    {
        std::cout << "The N value is invalid\n";
    }
    W = nextNumberInt(&input);;
    if (W < 1 )
    {
        std::cout << "The W value is invalid\n";
    }
        
    for(int i = 0; i < N*W; i++)
    {
        M->push_back(nextNumberDouble(&input));
    }
}

double Matrix::get(int i, int j)
{
    return M->at(i*N + j);
}

int Matrix::getRowSize()
{
    return W;
}

int Matrix::getColumnSize()
{
    return N;
}


int Matrix::nextNumberInt(std::string* input)
{
    int answer = atoi(input->c_str());

    while(input->at(0) == ' ')
        input->erase(0, 1);
    while(input->at(0) != ' ')
        input->erase(0, 1);
        
    return answer;
}

double Matrix::nextNumberDouble(std::string* input)
{
    double answer = atof(input->c_str());

    while(input->at(0) == ' ')
        input->erase(0, 1);
    while(input->at(0) != ' ')
        input->erase(0, 1);
        
    return answer;
}
