#include <time.h>

#include "../include/PSATsolver.hpp"
#include "../include/TestGenerator.hpp"

using namespace std;
using namespace arma;

void test(int N, int k, int n, double step, double begin, double end, string prefix);

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
    
    if((string) argv[1] == "--maketest")
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
    
    if((string) argv[1] == "--test")
    {
        test(atoi(argv[2]),
             atoi(argv[3]),
             atoi(argv[4]),
             atof(argv[5]),
             atof(argv[6]),
             atof(argv[7]),
             argv[8]);
        return 1;
    }
    
    int** matrix;
    int**& M = matrix;    
    vector<double> pi;
    double time;
    
    PSATsolver::solve(M, pi, &time, argv[1], true);
        
    return 1;
}

void test(int N,     int k,   int n,         double step, 
          double begin, double end, string prefix)
{
    int** matrix;
    int**& M = matrix;
    vector<double> pi;
    ofstream outtime;
    ofstream outsat;
    for(double i = begin; i <= end; i+=step)
    {
        outtime.open("./data/time/" + to_string((int) (i*10)) + ".txt");
        outsat.open("./data/sat/" + to_string((int) (i*10)) + ".txt");
        double y = 0;
        double sat = 0;
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
            cout << file << ": ";
            
            
            PSATsolver::solve(M, pi, &time, 
                             (char*) file.c_str(), false);
                             
            if (pi[0] == 1)
            {
                sat += 1.0/N;
                cout << "sat, time: ";
            }
            else cout << "unsat, time: ";
            
            cout << time << "\n";
            y += time/N;
        }
        outtime << i << " " << y << "\n";
        outsat << i << " " << sat << "\n"; 
        cout <<"media tempo: "<< y << "\n";
        cout <<"media sat: " << sat << "\n";
        outtime.close();
        outsat.close();
    }
}
