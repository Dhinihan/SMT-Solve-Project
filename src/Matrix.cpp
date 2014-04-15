//Includes
#include <iostream> 

//Header File
#include "../include/Matrix.hpp"

Matrix::Matrix(std::string input)
{
    M = new std::vector<double>;
    
    N = nextNumberInt(&input);;
    if (N < 1 )
    {
        std::cout << "The N value is invalid\n";
    }
        
    for(int i = 0; i < N; i++)
    {
        M->push_back(nextNumberDouble(&input));
    }
}

double Matrix::get(int i)
{
    return M->at(i);
}

int Matrix::getSize()
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
