//Includes
#include <iostream>
#include <fstream>
#include <string>

//Header File
#include "../include/Parser.hpp"

using namespace std;

Parser::Parser(char* inputPath)
{
    ifstream input(inputPath);
    
    if(!input.is_open())
    {
        cout << "Error while trying to open " 
             << inputPath 
             << "\n";
        exit(-1);
    }
    
    string buffer;
    string line;
    
    //Reading the input
    while(getline(input, line))
    {
        if(!isComment(&line))
        {
            buffer.insert(buffer.size(), line);
            buffer.insert(buffer.size(), " ");
        }
    }
    
    input.close();
    
    char check;
    if(nextChar(&buffer) != 'p'
    || nextChar(&buffer) != 'p'
    || nextChar(&buffer) != 'c'
    || nextChar(&buffer) != 'n'
    || nextChar(&buffer) != 'f')
    {
        cout << "The file is not in pcnf form." 
             << "\n";
         exit(-1);
    }
    
    int nVar     = nextNumberInt(&buffer);
    int nClauses = nextNumberInt(&buffer);
    int nProbs   = nextNumberInt(&buffer);
    int nBits    = nextNumberInt(&buffer);
    
    if(nVar     < 2
    || nClauses < 0
    || nProbs   < 1
    || nProbs   > nVar
    || nBits    < 2)
    {
        cout << "This is an invalid PSAT problem" 
             << "\n";
         exit(-1);
    }
    
    vector<double> temp(nVar, -1);
    probs = temp;
    
    for(int i = 0; i < nProbs; i++)
    {
        if(nextChar(&buffer) != 'a')
        {
            cout << "The probabilities lines must start with the char" 
                 << " \'a\'." 
                 << "\n";
            exit(-1);
        }
        probs[nextNumberInt(&buffer) - 1] = nextNumberDouble(&buffer);
    }
    
    for(int i = 0; i < nClauses; i++)
    {
        vector<int> tempClause;
        int var;
        while((var = nextNumberInt(&buffer)) != 0)
            tempClause.push_back(var);
        clauses.push_back(tempClause);
    }
    
    N = nProbs+1;
}

int Parser::getN()
{
    return N;
}

vector<double>& Parser::getProbs()
{
    return probs;
}

vector<vector<int>>& Parser::getClauses()
{
    return clauses;
}

int Parser::nextNumberInt(string* input)
{
    int answer = atoi(input->c_str());

    while(input->at(0) == ' ')
        input->erase(0, 1);
    while(input->at(0) != ' ')
        input->erase(0, 1);
        
    return answer;
}

double Parser::nextNumberDouble(string* input)
{
    double answer = atof(input->c_str());

    while(input->at(0) == ' ')
        input->erase(0, 1);
    while(input->at(0) != ' ')
        input->erase(0, 1);
        
    return answer;
}

char Parser::nextChar(string* input)
{
    while(input->at(0) == ' ')
        input->erase(0, 1);
        
    char answer = input->at(0);

    input->erase(0, 1);
        
    return answer;
}

bool Parser::isComment(string* input)
{
    for(int i = 0; i < input->length(); i++)
    {
        if(input->at(i) != ' ')
        {
            if(input->at(i) == 'c' || input->at(i) == 'C')
                return true;
            else
                return false;
        }
    }
    return false;
}
