//Includes
#include <fstream>
#include <iostream>
#include <cvc4/cvc4.h>


//Header File
#include "../include/Solver.hpp"
#include "../include/Matrix.hpp"
    
using namespace CVC4;

std::string Solver::find_x(std::string buffer, bool v)
{
    ExprManager em;
    SmtEngine smt(&em);
    
    smt.setOption("incremental", SExpr("true"));
    smt.setOption("produce-models", SExpr("true"));
    GetModelCommand cExample = GetModelCommand();
    
    std::vector<Expr> A = Solver::Avector(buffer, &em);
    
    int n = A.size();
    std::vector<Expr> X = Solver::Xvector(n, &em);
    
    Expr X_EQ_1_OR_0 = Solver::XDomain(X, &em); 
    Expr almost_one  = Solver::almostOne(X, &em);
    Expr only_one    = Solver::onlyOne(X, &em);
    Expr inequation  = Solver::inequation(X, A, &em);
    
    Expr assumptions = em.mkExpr(Kind::AND, X_EQ_1_OR_0, almost_one, only_one);
    smt.assertFormula(assumptions);
    
    smt.push();
    std::string isSat = smt.checkSat(inequation).toString();
    std::cout << "\nThe inequation is "<< isSat;
    if(isSat.compare("unsat"))
    {
        std::cout << " and a solution is:" << "\n";
        cExample.invoke(&smt);
        cExample.printResult(std::cout);
    }
    std::cout << "\n\n";
    smt.pop();

    if(v)
    {
        std::cout << "The inequation:" << "\n";
        std::cout << inequation  << "\n\n";
        std::cout << "The Domain for the variables:" << "\n";
        std::cout << X_EQ_1_OR_0 << "\n\n";
        std::cout << "Almost one of the variables must be equal to 1:" << "\n";
        std::cout << almost_one  << "\n\n";
        std::cout << "Only one of the variables must be equal to 1:" << "\n";
        std::cout << only_one    << "\n\n";
    }
    

    return "ok! " + std::to_string(n);
}

std::vector<Expr> Solver::Xvector(int n, ExprManager* em)
{
    std::vector<Expr> X;
    
    for(int i = 0; i < n-1; i++)
        X.push_back(em->mkVar("x" + std::to_string(i+1), em->integerType()));
    
    return X;
}

std::vector<Expr> Solver::Avector(std::string buffer,ExprManager* em)
{
    std::vector<Expr> A;
    
    Matrix coef(buffer);
    for(int i = 0; i < coef.getSize(); i++)
    {
        int temp = coef.get(i)*1000000;
        A.push_back(em->mkConst(Rational(temp,1000000)));
    }
    
    return A;
}

Expr Solver::XDomain(std::vector<Expr> X, ExprManager* em)
{
    std::vector<Expr> X_domain;
    
    Expr one  = em->mkConst(Rational(1));
    Expr zero = em->mkConst(Rational(0));
    
    Expr Xi_EQ_one;
    Expr Xi_EQ_zero;
    Expr tmp;
    
    for(int i = 0; i < X.size(); i++)
    {
        Xi_EQ_one  = em->mkExpr(Kind::EQUAL, X[i], one );
        Xi_EQ_zero = em->mkExpr(Kind::EQUAL, X[i], zero);
        X_domain.push_back(em->mkExpr(Kind::OR, Xi_EQ_one, Xi_EQ_zero));
    }
    
    return em->mkExpr(Kind::AND, X_domain);
}

Expr Solver::almostOne(std::vector<Expr> X, ExprManager* em)
{
    Expr one  = em->mkConst(Rational(1));
    std::vector<Expr> X_OR;
    
    for(int i = 0; i < X.size(); i++)
        X_OR.push_back(em->mkExpr(Kind::EQUAL, X[i], one));
    
    return em->mkExpr(Kind::OR, X_OR);
}

Expr Solver::onlyOne(std::vector<Expr> X, ExprManager* em)
{
    Expr only_one;
    Expr one = em->mkConst(Rational(1));
    std::vector<Expr> X_NEQ_one;
    Expr tmp;
    
    for(int i = 0; i < X.size(); i++)
        X_NEQ_one.push_back(em->mkExpr(Kind::DISTINCT, X[i], one));
    
    for(int i = 0; i < X_NEQ_one.size() - 1; i++)
        for(int j = i+1; j < X_NEQ_one.size(); j++)
        {
            if(i == 0 && j == 1)
                only_one = em->mkExpr(Kind::OR, X_NEQ_one[i], X_NEQ_one[j]);
            else
            {
                tmp = em->mkExpr(Kind::OR, X_NEQ_one[i], X_NEQ_one[j]);
                only_one = em->mkExpr(Kind::AND, only_one, tmp);
            }
        }
            
    return only_one;
}

Expr Solver::inequation(std::vector<Expr> X, std::vector<Expr> A, ExprManager* em)
{
    
    Expr x_MUL_a;
    Expr zero = em->mkConst(Rational(0));
    Expr inequation;
    
    std::vector<Expr> Xi_MUL_Ai;
    
    Xi_MUL_Ai.push_back(A[0]);
    
    for(int i = 0; i < X.size(); i++)
    {
        x_MUL_a = em->mkExpr(Kind::MULT, X[i], A[i+1]);
        Xi_MUL_Ai.push_back(x_MUL_a);
    }
    
    inequation = em->mkExpr(Kind::PLUS, Xi_MUL_Ai);
    
    return em->mkExpr(Kind::GEQ, inequation, zero);
}
