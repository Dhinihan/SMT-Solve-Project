#include <time.h>

#include "../include/PSATsolver.hpp"
#include "../include/TestGenerator.hpp"

using namespace std;
using namespace arma;

int main(int argc, char** argv)
{
    bool v;
    if(argc < 20)
        v = true;
    else
        v = false;
    
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
    
    int** m;
    int**& M = m;
    vector<double> pi;
    double time;
    int n;
    
    for(int i = 1; i < argc; i++)
    {
        n = PSATsolver::solve(M, pi, &time, argv[i], v);
        cout << argv[i] << ": " << time << "\n";
    }
    
    
    return 1;
}
