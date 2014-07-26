#ifndef CVC4SOLVER_H
#define CVC4SOLVER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cvc4/cvc4.h>

using namespace CVC4;
using namespace std;

//!  A interface with the CVC4.
/*!  
 *  A static class to to make CVC4 opperations.
 *  \author  Vinícius Nascimento Silva
 *  \since   05/21/14
 */
class CVC4Solver
{
    private:
        //! Construtor.
        /*!
         *  Cannot create instances.
         */
        CVC4Solver();
        
        static const int delta = 100000;
        
        //! Creates the variables.
        /*!
         * \param n  the size of the words.
         * \param w  the number of words. 
         * \param em the CVC4's expression manager.
         * \return   a vector with the variables.
         * \sa       solveInequation()
         */
        static vector<Expr> Xvector(int n, 
                                    vector<int>& free,
                                    ExprManager* em);
        
        //! Creates the vector of coefficients.
        /*!
         * \param coef the vector with the coefficients values.
         * \param em   the CVC4's expression manager.
         * \return     a vector with the expressions of the coefficients.
         * \sa         solveInequation()
         */
        static vector<Expr> Avector(vector<double>& coef, 
                                    ExprManager* em);
        
        //! Creates the domain of the variables, witch is (Xi = 0 or Xi = 1) for each i.
        /*!
         * \param X  the vector with the variable expressions.
         * \param em the CVC4's expression manager.
         * \return   a expression with the domain of the variables.
         * \sa       solveInequation()
         */
        static Expr XDomain(vector<Expr>& X, ExprManager* em);
                
        static Expr makeClauses(vector<Expr>&        X,
                                vector<vector<int>>& clauses,
                                ExprManager*         em);
        
        //! Creates a expression with the desired inequation.
        /*! The inequation is in the form of A0 + Ai*Xi >= 0. where i
         *  goes from 1 to n*w
         *
         * \param X  the vector with the variable expressions.
         * \param A  the vector with the coefficients.
         * \param em the CVC4's expression manager.
         * \return   a expression with the domain of the variables.
         * \sa       solveInequation()
         */
        static Expr inequation(vector<Expr>& X, 
                               vector<Expr>& A,
                               vector<int>& free,
                               ExprManager* em);
        
    public:
        
        //! Find if the inequation is satisfiable and give one answer if possible.
        /*! The inequation is in the form of A0 + A[i,j]*X[i,j] >= 0. 
         *  where i goes from 1 to w and j goes from 1 to n. 
         *  The domain of the x in the output is (X[i,j] = 0 or X[i,j]
         *  = 1).
         *  For each i exists only one j that X[i,j] = 1.
         *  the response R[0] is equal to 1 if it is satisfiable  
         *  and the values for each X[i,j] is in the form 
         *  X[i,j] = R[(i-1)*n + j].
         *  If not satisfiable, R[0] = 0. 
         *
         * \param coef the vector with the coefficients.
         * \param n  the size of the words.
         * \param w  the number of words.
         * \param v  if is true, it prints the process.
         * \return   a vector with one solution if possible.
         */
        static vector<int> solve(vector<double>& coef,
                                 vector<int>& free,
                                 vector<vector<int>>& clauses,
                                 int n,
                                 bool v = false);
};

#endif
