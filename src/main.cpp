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
    
    if (argc == 3 && argv[2][1] == 'v' && argv[2][0] == '-')
        v = true;
    
    int** m;
    int**& M = m;
    vector<double> pi;
    double time;
    int n;
    
    n = PSATsolver::solve(M, pi, &time, argv[1], v);

    cout << time << "\n\n";
    
    return 1;
}
