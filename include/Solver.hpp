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
        
        static std::vector<CVC4::Expr> Xvector(int n, CVC4::ExprManager* em);
        
        static std::vector<CVC4::Expr> Avector(std::string buffer, CVC4::ExprManager* em);
        
        static CVC4::Expr XDomain(std::vector<CVC4::Expr> X, CVC4::ExprManager* em);
        
        static CVC4::Expr almostOne(std::vector<CVC4::Expr> X, CVC4::ExprManager* em);
        
        static CVC4::Expr onlyOne(std::vector<CVC4::Expr> X, CVC4::ExprManager* em);
        
        static CVC4::Expr inequation(std::vector<CVC4::Expr> X, std::vector<CVC4::Expr> A, CVC4::ExprManager* em);
        
    public:
        /* Method find_x: return the x that keep the equation 
         *                positiive.
         *
         * parameter buffer: string with the coefficients.
         */
        static std::string find_x(std::string buffer, bool v);
           
};

#endif