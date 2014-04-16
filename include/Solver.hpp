#ifndef SOLVER_teste_H
#define SOLVER_teste_H

#include <string>
#include <vector>
#include <cvc4/cvc4.h>

/*  Class CVC
 *  
 *  A static class to to make CVC4 opperations.
 */
class Solver
{
    private:
        /*Cannot create instaces*/
        Solver();
        
        static std::vector<CVC4::Expr> Xvector(int n, int w, CVC4::ExprManager* em);
        
        static std::vector<CVC4::Expr> Avector(std::vector<double>& coef, CVC4::ExprManager* em);
        
        static CVC4::Expr XDomain(std::vector<CVC4::Expr>& X, CVC4::ExprManager* em);
        
        static CVC4::Expr almostOne(std::vector<CVC4::Expr>& X, int n, int w, CVC4::ExprManager* em);
        
        static CVC4::Expr onlyOne(std::vector<CVC4::Expr>& X, int n, int w, CVC4::ExprManager* em);
        
        static CVC4::Expr inequation(std::vector<CVC4::Expr>& X, std::vector<CVC4::Expr>& A, CVC4::ExprManager* em);
        
    public:
        /* Method find_x: return the x that keep the equation 
         *                positiive.
         *
         * parameter buffer: string with the coefficients.
         */
        static void find_x(std::vector<double>& coef, int n, int w, bool v=false);
           
};

#endif
