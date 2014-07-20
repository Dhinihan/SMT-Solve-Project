#ifndef TestGenerator_H
#define TestGenerator_H

#include<string>

using namespace std;

class TestGenerator
{
    private:
    
    int randBetween(int min, int max);
    
    public:
    
    TestGenerator(int seed = 0);
    
    bool create(int k, int n, int m, string path);
    bool createN(int N, int k, int n, int m, string prefix);
    bool createAll(int N, 
                   int k, 
                   int n, 
                   double step, 
                   int begin, 
                   int end,
                   string prefix);
    
};

#endif
