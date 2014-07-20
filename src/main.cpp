#include "../include/PSATsolver.hpp"

using namespace std;
using namespace arma;

int main(int argc, char** argv)
{
    bool v = false;
    
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
    
    for(int i = 0; i < argc; i++)
    {
        n = PSATsolver::solve(M, pi, &time, argv[i], v);
        cout << time << "\n";
    }
    
    
    return 1;
}
