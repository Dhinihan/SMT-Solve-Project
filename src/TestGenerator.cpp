#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<climits>
#include<math.h>
    
#include "../include/TestGenerator.hpp"

using namespace std;

TestGenerator::TestGenerator(int seed)
{   
    srand(seed);
}

bool TestGenerator::create(int k, int n, int m, string path)
{
    ofstream output;
    output.open(path);
    if(!output.is_open())
        return false;
    output << "p " << "pcnf " 
           << n << " " 
           << m << " " 
           << k << " " 
           << 2 << "\n";
    for(int i = 0; i < k; i++)
    {
        output << "a "
               << i+1 << " "
               << randBetween(1, 100)/100.0 << "\n";
    }
    
    for(int i = 0; i < m; i++)
    {
        int a = randBetween(1,n);
        int b, c;
        while((b = randBetween(1,n)) == a);
        while((c = randBetween(1,n)) == a && c == b);
        if(randBetween(1,2) == 1)
            output << '-';
        output << a << " ";
        if(randBetween(1,2) == 1)
            output << '-';
        output << b << " ";
        if(randBetween(1,2) == 1)
            output << '-';
        output << c << " 0\n";
    }
    
    output.close();
    return true;
}

bool TestGenerator::createN(int N, int k, int n, int m, string prefix)
{
    for(int i = 0; i < N; i++)
        if(!create(k,n,m,
                  prefix + 
                  "_K" + to_string(k) + 
                  "_N" + to_string(n) +
                  "_M" + to_string(m) +
                  "_"  + to_string(i) +
                  ".pcnf"))
            return false;
    return true;
}

bool TestGenerator::createAll(int N, 
                              int k, 
                              int n, 
                              double step, 
                              int begin, 
                              int end, 
                              string prefix)
{
    for(double i = begin; i <= end; i+=step)
    {
        int m = round(n*i);
        cout << m << "\n";
        createN(N, k, n, m, prefix);
    }
    return true;
}


int TestGenerator::randBetween(int min, int max)
{
    return ceil((rand()/(INT_MAX*1.0))*(max-min+1)) + min - 1;
}
