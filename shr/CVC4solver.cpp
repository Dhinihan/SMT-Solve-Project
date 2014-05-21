#include "../include/Solver.hpp"

using namespace CVC4;
using namespace std;

vector<int> Solver::find_x(std::vector<double>& coef, int n, int w, bool v)
{
    ExprManager em;
    SmtEngine smt(&em);
    
    vector<int> result;
    
    smt.setOption("incremental", SExpr("true"));
    smt.setOption("produce-models", SExpr("true"));
    GetModelCommand cExample = GetModelCommand();
    
    vector<Expr> A = Solver::Avector(coef, &em);
    
    vector<Expr> X = Solver::Xvector(n, w, &em);
    
    Expr X_EQ_1_OR_0 = Solver::XDomain   (X, &em); 
    Expr almost_one  = Solver::almostOne (X, n, w, &em);
    Expr only_one    = Solver::onlyOne   (X, n, w, &em);
    Expr inequation  = Solver::inequation(X, A, &em);
    
    Expr assumptions = em.mkExpr(Kind::AND, X_EQ_1_OR_0, almost_one, only_one);
    smt.assertFormula(assumptions);
    
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
        cout << "Almost one of the variables must be equal to 1:" << "\n";
        cout << almost_one  << "\n\n";
        cout << "Only one of the variables must be equal to 1:" << "\n";
        cout << only_one    << "\n\n";
    }
    
    if(sat)
        for(int i = 0; i < X.size(); i++)
            result.push_back(atoi(smt.getValue(X[i]).toString().c_str()));
    else
        result.push_back(-1);
    
    smt.pop();    
    
    return result;
    
}

vector<Expr> Solver::Xvector(int n, int w, ExprManager* em)
{
    vector<Expr> X;
    
    for(int i = 0; i < w; i++)
        for(int j = 0; j < n; j++)
            X.push_back(em->mkVar("x" + to_string(i+1) + to_string(j+1), em->integerType()));
    
    return X;
}

vector<Expr> Solver::Avector(vector<double>& coef, ExprManager* em)
{
    vector<Expr> A;
    
    for(int i = 0; i < coef.size(); i++)
    {
        int temp = coef[i]*1000000;
        A.push_back(em->mkConst(Rational(temp,1000000)));
    }
    
    return A;
}

Expr Solver::XDomain(vector<Expr>& X, ExprManager* em)
{
    vector<Expr> X_domain;
    
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

Expr Solver::almostOne(vector<Expr>& X, int n, int w, ExprManager* em)
{
    Expr one  = em->mkConst(Rational(1));
    vector<Expr> X_EQ_One;
    vector<Expr> X_AND;
    vector<Expr> X_OR;
    
    for(int i = 0; i < X.size(); i++)
        X_EQ_One.push_back(em->mkExpr(Kind::EQUAL, X[i], one));
    
    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < n ; j++)
            X_OR.push_back(X_EQ_One[i*n+j]);
            
        X_AND.push_back(em->mkExpr(Kind::OR, X_OR));
        X_OR.clear();
    }
    
    return em->mkExpr(Kind::AND, X_AND);

}

Expr Solver::onlyOne(vector<Expr>& X, int n, int w, ExprManager* em)
{
    Expr only_one;
    Expr one = em->mkConst(Rational(1));
    vector<Expr> X_NEQ_one;
    vector<Expr> X_AND;
    
    for(int i = 0; i < X.size(); i++)
        X_NEQ_one.push_back(em->mkExpr(Kind::DISTINCT, X[i], one));
        
    for(int i = 0; i < w; i++)
    {
        for(int j = i*n; j < i*n + n-1; j++)
            for (int k = j+1; k < i*n + n; k++)
                X_AND.push_back(em->mkExpr(Kind::OR, 
                                           X_NEQ_one[j], 
                                           X_NEQ_one[k]));
    }
    
    return em->mkExpr(Kind::AND, X_AND);
}

Expr Solver::inequation(vector<Expr>& X, vector<Expr>& A, ExprManager* em)
{
    
    Expr x_MUL_a;
    Expr zero = em->mkConst(Rational(0));
    Expr inequation;
    
    vector<Expr> Xi_MUL_Ai;
    
    Xi_MUL_Ai.push_back(A[0]);
    
    for(int i = 0; i < X.size(); i++)
    {
        x_MUL_a = em->mkExpr(Kind::MULT, X[i], A[i+1]);
        Xi_MUL_Ai.push_back(x_MUL_a);
    }
    
    inequation = em->mkExpr(Kind::PLUS, Xi_MUL_Ai);
    
    return em->mkExpr(Kind::GEQ, inequation, zero);
}
