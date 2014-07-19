#include <iostream>
#include <math.h>

#include "../include/PSATsolver.hpp"
#include "../include/CVC4solver.hpp"
#include "../include/Parser.hpp"

using namespace std;
using namespace arma;

void PSATsolver::solve(char* inputPath, bool v)
{
    Parser problem(inputPath);
    solve(problem.getN(), problem.getProbs(), problem.getClauses(), v);
}

void PSATsolver::solve(int n, 
                       vector<double> prob, 
                       vector<vector<int>> clauses,
                       bool v)
{
    vector<double> cleaned;
    vector<int> extra;
    
    cleaned.push_back(1);
    
    for(int i = 0; i < prob.size(); i++)
        if(prob[i] == -1)
            extra.push_back(i);
        else
            cleaned.push_back(prob[i]);
    
    mat c = ones<mat>(n,1);
    mat B = eye<mat>(n,n);
    mat p = vectorToMat(cleaned);

    mat pi = p;
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
    while(z(0,0) > 0.00000001)
    {
        
        vector<double> coeffs = matToVector(c.t()*B.i());
           
        if(v)
            cout << z << "\n";
        
        vector<int> sol = CVC4Solver::solve(coeffs, 
                                            extra, 
                                            clauses,
                                            n-1);
        
        if(sol[0] == 0)
        {
            cout << "Unsat" << "\n";
            if(v)
                cout << count << " iterações\n";
            return;
        }
        
        mat teste = (c.t()*B.i())*vectorToMat(sol);
        if (teste(0,0) < min)
            min = teste(0,0);
        if(v)
            cout << "min: " << min << "\n";
        
        pivoting(B, pi, c, vectorToMat(sol), p, v);
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
    }
    
    cout << "B:\n" << B << "\n";
    cout << "pi:\n" << pi << "\n";
}

vector<double> PSATsolver::matToVector(mat A)
{
    vector<double> v;
    for(int i = 0; i < A.n_cols; i++)
    {
        int temp;
        if(A(0,i) >= 0)
            temp = A(0,i)*100000;
        else
            temp = ceil(A(0,i)*100000);
        v.push_back(temp/10000000.0);
    }
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

void PSATsolver::pivoting(mat& B, 
                          mat& pi, 
                          mat& c, 
                          mat Aj, 
                          mat p, 
                          bool v)
{
    double min = 2;
    int minIndex = -1;
    
    mat Xj = B.i()*Aj;
    
    for(int i = 0; i < Xj.n_rows; i++)
    {
        if(Xj(i,0) > 0.000001 && pi(i,0)/Xj(i,0) < min)
        {
            min = pi(i,0)/Xj(i,0);
            minIndex = i;
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
