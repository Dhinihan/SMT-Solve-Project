#include "../include/CVC4solver.hpp"

#include <math.h>

using namespace CVC4;
using namespace std;


vector<int> CVC4Solver::solve(vector<double>& coef,
                              vector<int>& free,
                              vector<vector<int>>& clauses,
                              int n,
                              bool v)
{
    ExprManager em;
    SmtEngine smt(&em);
    
    vector<int> result;
    
    smt.setOption("incremental", SExpr("true"));
    smt.setOption("produce-models", SExpr("true"));
    GetModelCommand cExample = GetModelCommand();
    
    vector<Expr> A = Avector(coef, &em);
    
    vector<Expr> X = Xvector(n, free, &em);
    
    Expr X_EQ_1_OR_0 = XDomain(X, &em); 
    
    Expr restrictions = makeClauses(X, clauses, &em); 
    
    Expr inequation  = CVC4Solver::inequation(X, A, free, &em);
    
    smt.assertFormula(em.mkExpr(Kind::AND, X_EQ_1_OR_0, restrictions));
    
    smt.push();
    string isSat = smt.checkSat(inequation).toString();
    bool sat = isSat.compare("unsat");
    
    if(v)
    {
        cout << "\nThe inequation is "<< isSat;
        if(sat)
        {
            cout << " and a solution is:" << "\n";
            cExample.invoke(&smt);
            cExample.printResult(cout);
        }
        cout << "\n\n";
        
        cout << "The inequation:" << "\n";
        cout << inequation  << "\n\n";
        cout << "The Domain for the variables:" << "\n";
        cout << X_EQ_1_OR_0 << "\n\n";
    }
    
    if(sat)
    {
        result.push_back(1);
        for(int i = 0, j = 0; i < X.size(); i++)
        {
            if(free.size() > 0 && i == free[j])
                j++;
            else
            {
                string temp = smt.getValue(X[i]).toString();
                if(temp.at(0) == '(')
                    result.push_back(atoi(temp.substr(16).c_str()));
                else
                    result.push_back(atoi(temp.substr(0).c_str()));
            }
        }
    }
    else
    {
        result.push_back(0);
        for(int i = 0; i < X.size(); i++)
            result.push_back(0);
    }
    smt.pop();    

    return result;
    
}

bool CVC4Solver::isSat(vector<int>&         col,
                       vector<int>&         free,
                       vector<vector<int>>& clauses,
                       int                  n,
                       bool                 v)
{
    ExprManager em;
    SmtEngine smt(&em);
    
    smt.setOption("incremental", SExpr("true"));
    smt.setOption("produce-models", SExpr("true"));
    GetModelCommand cExample = GetModelCommand();
    
    vector<Expr> X = Xvector(n, free, &em);
    
    Expr X_EQ_1_OR_0 = XDomain(X, &em);
    
    Expr restrictions = makeClauses(X, clauses, &em); 
    
    smt.assertFormula(em.mkExpr(Kind::AND, X_EQ_1_OR_0, restrictions));
    
    Expr column_assertions = assertColumn(X ,col, free, &em);
    
    smt.push();
    
    string isSat = smt.checkSat(column_assertions).toString();
    
    smt.pop();
    
    return !isSat.compare("unsat");
}

vector<Expr> CVC4Solver::Xvector(int n, 
                                 vector<int>& free, 
                                 ExprManager* em)
{
    vector<Expr> X;
    
    for(int i = 0; i < n + free.size(); i++)
        X.push_back(em->mkVar("x" + to_string(i+1), 
                              em->integerType()));
    
    return X;
}

vector<Expr> CVC4Solver::Avector(vector<double>& coef, ExprManager* em)
{
    vector<Expr> A;
    
    for(int i = 0; i < coef.size(); i++)
    {
        int temp = delta;
        A.push_back(em->mkConst(Rational(ceil(temp*coef[i]), temp)));
    }
    
    return A;
}

Expr CVC4Solver::XDomain(vector<Expr>& X, ExprManager* em)
{
    vector<Expr> X_domain;
    
    Expr one  = em->mkConst(Rational(1));
    Expr zero = em->mkConst(Rational(0));
    
    Expr Xi_EQ_one;
    Expr Xi_EQ_zero;
    
    for(int i = 0; i < X.size(); i++)
    {
        Xi_EQ_one  = em->mkExpr(Kind::EQUAL, X[i], one );
        Xi_EQ_zero = em->mkExpr(Kind::EQUAL, X[i], zero);
        X_domain.push_back(em->mkExpr(Kind::OR, 
                                      Xi_EQ_one, 
                                      Xi_EQ_zero));
    }
    
    return em->mkExpr(Kind::AND, X_domain);
}

Expr CVC4Solver::makeClauses(vector<Expr>&        X,
                             vector<vector<int>>& clauses,
                             ExprManager*         em)
{
    vector<Expr> temp;
    vector<Expr> assertions;
    Expr         expression;
    
    Expr one  = em->mkConst(Rational(1));
    Expr zero = em->mkConst(Rational(0));
    
    for(int i = 0; i < clauses.size(); i++)
    {
        for(int j = 0; j < clauses[i].size(); j++)
        {
            if(clauses[i][j] < 0)
            {
                int index = -clauses[i][j];
                expression = em->mkExpr(Kind::EQUAL, X[index-1], zero);
            }
            else
            {
                int index  = clauses[i][j];
                expression = em->mkExpr(Kind::EQUAL, X[index-1], one);
            }
            temp.push_back(expression);
        }
        if(temp.size() > 1)
            assertions.push_back(em->mkExpr(Kind::OR, temp));
        else
            assertions.push_back(temp[0]);
        temp.clear();
    }
    
    return em->mkExpr(Kind::AND, assertions);
}                  

Expr CVC4Solver::assertColumn(vector<Expr>& X, 
                              vector<int>& col,
                              vector<int>& free,
                              ExprManager* em)
{
    vector<Expr> colsAssertions;
    
    Expr one  = em->mkConst(Rational(1));
    Expr zero = em->mkConst(Rational(0));
    
    for(int i = 0, j = 0; i < X.size(); i++)
    {
        if(free.size() > 0 && i == free[j])
            j++;
        else
        {
            if(col[i] == 1)
                colsAssertions.push_back(em->mkExpr(Kind::EQUAL, 
                                                    X[i], 
                                                    one));
            else
                colsAssertions.push_back(em->mkExpr(Kind::EQUAL, 
                                                    X[i], 
                                                    zero));
        }
    }
    
    return em->mkExpr(Kind::AND, colsAssertions);
}

Expr CVC4Solver::inequation(vector<Expr>& X, 
                            vector<Expr>& A,
                            vector<int>& free,
                            ExprManager* em)
{
    Rational error((int) A.size(), delta);
    
    Expr x_MUL_a;
    Expr zero = em->mkConst(error);
    Expr inequation;
    
    vector<Expr> Xi_MUL_Ai;
    
    Xi_MUL_Ai.push_back(A[0]);
    
    for(int i = 0, j = 0; i < X.size(); i++)
    {
        if(free.size() > 0 && i == free[j])
            j++;
        else
        {
            x_MUL_a = em->mkExpr(Kind::MULT, X[i], A[i+1-j]);
            Xi_MUL_Ai.push_back(x_MUL_a);
        }
    }
    
    inequation = em->mkExpr(Kind::PLUS, Xi_MUL_Ai);
    
    return em->mkExpr(Kind::GT, inequation, zero);
}
