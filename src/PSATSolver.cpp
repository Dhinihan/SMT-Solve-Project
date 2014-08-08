#include <iostream>
#include <math.h>
#include <sys/times.h>

#include "../include/PSATsolver.hpp"
#include "../include/CVC4solver.hpp"
#include "../include/Parser.hpp"

using namespace std;
using namespace arma;

int PSATsolver::solve(int**& m, 
                      vector<double>& prob, 
                      double* time,
                      char* inputPath, 
                      bool v)
{
    Parser problem(inputPath);
    prob = problem.getProbs();
    
    return solve(m, 
                 prob,
                 time, 
                 problem.getClauses(), 
                 v);
}

int PSATsolver::solve(int**& m, 
                      vector<double>& prob,
                      double* time,
                      vector<vector<int>> clauses,
                      bool v)
{
    struct tms tmsstart, tmsend;
    clock_t    start, end;
    
    static long clktck = 0;
    
    if ((clktck = sysconf(_SC_CLK_TCK)) < 0)
            cout << "sysconf error" << endl;

    if ((start = times(&tmsstart)) == -1)
        cout << "times error" << endl;

    double delta = CVC4Solver::getDelta();
        
    vector<double> cleaned;
    vector<int> extra;
    
    cleaned.push_back(1);
    
    for(int i = 0; i < prob.size(); i++)
        if(prob[i] == -1)
            extra.push_back(i);
        else
            cleaned.push_back(prob[i]);
    
    int n = cleaned.size();
    
    mat B = supTriangle(n, cleaned);
    mat c = makeCostVector(n, B, extra, clauses);
    mat p = vectorToMat(cleaned);

    mat pi = B.i()*p;
    mat z = c.t()*pi;
    
    if(v)
    {
        cout << "c:\n" << c << "\n";
        cout << "B:\n" << B << "\n";
        cout << "p:\n" << p << "\n";
        cout << "pi:\n" << pi << "\n";
        cout << "c*pi:" << z(0,0) << "\n";
    }
    
    int count = 0;
    double min = 1;
    
    vector<mat> partialSolutions;
    
    while(z(0,0) > delta)
    {
        vector<double> coeffs = matToVector(c.t()*B.i());
        int solIndex;
        mat sol;
        
        if(v)
            cout << z << "\n";

        solIndex = findSolutions(partialSolutions, coeffs);
        if(solIndex > -1)
            sol = partialSolutions[solIndex];
        else
        {
            
            vector<int> newSolution = CVC4Solver::solve(coeffs, 
                                                        extra, 
                                                        clauses,
                                                        n-1);
            if(newSolution[0] == 0)
            {
                if(v)
                {
                    cout << "Unsat" << "\n";
                    cout << count << " iterations\n";
                }
                if ((end = times(&tmsend)) == -1)
                    cout << "times error" << endl;
                
                prob.clear();
                prob.push_back(0);
                
                *time = ((tmsend.tms_utime - tmsstart.tms_utime) / 
                        (double) clktck);   

                return n;
            }
            
            sol = vectorToMat(newSolution);
            partialSolutions.push_back(sol);
        }
        

        mat teste = (c.t()*B.i())*sol;
        if (teste(0,0) < min)
            min = teste(0,0);
        if(v)
            cout << "min: " << min << "\n";
        
        pivoting(B, pi, c, sol, p, v);
        z = c.t()*pi;
        
        count++;
    }
    
    mat onlyones = ones<mat>(n,1);
    
    if(v)
    {
        cout << "c:\n" << c << "\n";
        cout << "p:\n" << p << "\n";
        cout << "c*pi:\n" << z(0,0) << "\n";
        cout << "tem que ser 1: " << onlyones.t()*pi << "\n";
        cout << "tem que ser p:\n" << B*pi << "\n";
        cout << count << " iterações\n";
        cout << "B:\n" << B << "\n";
        cout << "pi:\n" << pi << "\n";
    }
    
    int** matrix = makeMatrix(n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            matrix[i][j] = B(i,j);
    
    prob.clear();
    prob.push_back(1);
    
    for(int i = 0; i < pi.size(); i++)
        prob.push_back(pi(i,0));
    
    m = matrix;
    
    if ((end = times(&tmsend)) == -1)
        cout << "times error" << endl;
        
    *time = ((tmsend.tms_utime - tmsstart.tms_utime) / 
           (double) clktck);   
       
    return n;        
}

mat PSATsolver::supTriangle(int n, vector<double>& probs)
{

    vector<double*> probsWithIndex;
    for(int i = 0; i < probs.size(); i++)
    {
        double* temp = (double*) malloc((sizeof (double))*2);
        temp[0] = probs[i];
        temp[1] = (double) i;
        
        probsWithIndex.push_back(temp);
    }
    
    sort(probsWithIndex.begin(), probsWithIndex.end(), lessProbs);
    
    mat matrix = ones<mat>(n,n);
    for(int i = 0; i < probs.size(); i++)
        for(int j = 0; j < probs.size() - i - 1; j++)
	{
	    int row = rint(probsWithIndex[i][1]);
	    matrix(row, j) = 0;
	}
    return matrix;
}

mat PSATsolver::makeCostVector(int                  n,
                               mat                  B, 
                               vector<int>&         free, 
                               vector<vector<int>>& clauses)
{
    mat c = ones<mat>(n,1);
    for(int i = 0; i < B.n_cols; i++)
    {
        vector<int> col = matToVector(B.col(i));
        bool sat = CVC4solver::isSat(col, free, clauses, n);
        if(sat)
            c(i,0) = 0.0;
    }
    cout << c;
    exit(-1);
    return c;
}                               
                               

vector<double> PSATsolver::matToVector(mat A)
{
    double iDelta = 1/CVC4Solver::getDelta();
    vector<double> v;
    for(int i = 0; i < A.n_cols; i++)
    {
        
        int temp;
        if(A(0,i) >= 0)
            temp = A(0,i)*iDelta;
        else
            temp = ceil(A(0,i)*iDelta);
        v.push_back(temp/iDelta);
    }
    return v;
}

vector<int> PSATsolver::matToVector(mat A)
{
    double iDelta = 1/CVC4Solver::getDelta();
    vector<int> v;
    for(int i = 0; i < A.n_cols; i++)
        v.push_back(rint(A(i,0)));
    return v;
}


mat PSATsolver::vectorToMat(vector<int>& v)
{
    mat A(v.size(), 1);
    for(int i = 0; i < A.n_rows; i++)
    {
        A(i,0) = v[i];
    }
    return A;
}

mat PSATsolver::vectorToMat(vector<double>& v)
{
    mat A(v.size(), 1);
    for(int i = 0; i < A.n_rows; i++)
    {
        A(i,0) = v[i];
    }
    return A;
}

int** PSATsolver::makeMatrix(int n)
{
    int** matrix = (int**) malloc((sizeof (int*)) * n);
    for(int i = 0; i < n; i ++)
        matrix[i] = (int*) malloc((sizeof (int)) * n);
        
    return matrix;
}

void PSATsolver::pivoting(mat& B, 
                          mat& pi, 
                          mat& c, 
                          mat Aj, 
                          mat p, 
                          bool v)
{
    double delta = CVC4Solver::getDelta();
    double min = 2;
    int minIndex = -1;

    mat Xj = B.i()*Aj;

    for(int i = 0; i < Xj.n_rows; i++)
    {
	if(Xj(i,0) > delta && pi(i,0)/Xj(i,0) < min - delta)
        {
	
            min = pi(i,0)/Xj(i,0);
            minIndex = i;
	    if (min < delta)
		break;
	    
        }
    }
    B.insert_cols(minIndex, Aj);
    B.shed_col(minIndex+1);
    
    c(minIndex,0) = 0;
    
    if(v)
        cout << "B:\n" << B << "\n";
    
    if(arma::rank(B) < B.n_cols)
    {
        cout << "Caso degenerado" << "\n";
        exit(-1);
    }

    pi = B.i()*p;
}

int PSATsolver::findSolutions(vector<mat>& matrix, mat coeffs)
{
    double delta = CVC4Solver::getDelta();
    
    for(int i = 0; i < matrix.size(); i++)
    {
        mat check = coeffs.t()*matrix[i];
        if(check(0,0) > delta*matrix[i].n_rows)
            return i;
    }
    return -1;
}

bool PSATsolver::lessProbs(double *a, double* b)
{
    return a[0] < b[0];
}
