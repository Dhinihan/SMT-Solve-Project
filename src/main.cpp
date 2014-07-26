#include <time.h>

#include "../include/PSATsolver.hpp"
#include "../include/TestGenerator.hpp"

using namespace std;
using namespace arma;

void test(int N, int k, int n, double step, int begin, int end, string prefix);

int main(int argc, char** argv)
{
    bool v;
    if(argc < 20)
        v = true;
    else
        v = false;
    
    if (argc < 2)
    {
        std::cout << "I need a input file " << "\n";
        return -1;
    }
    
    if((string) argv[1] == "--test")
    {
        TestGenerator t(atoi(argv[2]));
        t.createAll(atoi(argv[3]),
                    atoi(argv[4]),
                    atoi(argv[5]),
                    atof(argv[6]),
                    atoi(argv[7]),
                    atoi(argv[8]),
                    argv[9]);
        return 1;
    }

    if (argc < 2)
    {
        std::cout << "I need a input file " << "\n";
        return -1;
    }
    
    //if (argc == 3 && argv[2][1] == 'v' && argv[2][0] == '-')
      //  v = true;
    
        test(atoi(argv[1]),
             atoi(argv[2]),
             atoi(argv[3]),
             atof(argv[4]),
             atoi(argv[5]),
             atoi(argv[6]),
             argv[7]);
    
    
    
    return 1;
}

void test(int N, int k, int n, double step, int begin, int end, string prefix)
{
    int** matrix;
    int**& M = matrix;
    vector<double> pi;
    ofstream output;
    output.open("./data/data.txt");
       
    for(double i = begin; i <= end; i+=step)
    {
        double y = 0;
        for(int j = 0; j < N; j++)
        {
            double time = 0;
            int m = round(n*i);
            string file = prefix;
            file += "_K" + to_string(k)
                 +  "_N" + to_string(n)
                 +  "_M" + to_string(m)
                 +  "_"  + to_string(j)
                 +  ".pcnf";
            PSATsolver::solve(M, pi, &time, (char*) file.c_str(), false);
            cout << j << " " << time << "\n";
            y += time/N;
        }
        output << i << " " << y << "\n";
        cout <<"media: "<< y << "\n";
    }
    output.close();   
}
