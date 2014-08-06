#ifndef PSATSOLVER_H
#define PSATSOLVER_H

#include <vector>
#include <armadillo>

using namespace std;
using namespace arma;


//!  A PSAT Solver
/*!  
 *  A static class to solve PSAT problems.
 *  \author  Vinícius Nascimento Silva
 *  \since   07/09/14
 */
class PSATsolver
{
    private:
        //! Constructor.
        /*!
         *  Cannot create instances.
         */
        PSATsolver();
        
        //! Transforms unidimensional matrix to vector.
        /*!
         * \param A  A unidimensional matrix.
         * \return   a vector representing the matrix.
         * \sa       solve()
         */
        static vector<double> matToVector(mat A);
        
        //! Transforms an integer vector to a one dimensional matrix.
        /*!
         * \param v  The vector to be transformed.
         * \return   A unidimensional matrix.
         * \sa       solve()
         */
        static mat vectorToMat(vector<int>& v);
        
        //! Transforms a double vector to a one dimensional matrix.
        /*!
         * \param v  The vector to be transformed.
         * \return   A unidimensional matrix.
         * \sa       solve()
         */
        static mat vectorToMat(vector<double>& v);
        
        //! The process of pivoting of the simplex.
        /*! This method insert a column that reduce the cost, and 
         *  updates the the problem to a new iteration 
         * \param B  The Base matrix of the problem.
         * \param pi The actual value of the simplex variables.
         * \param c  The cost of each simplex variable.
         * \param Aj The column that satisfy the restrictions.
         * \param p  The probabilities of each PSAT problem variables.
         * \sa       solve()
         */
        static void pivoting(mat& B, 
                             mat& pi, 
                             mat& c, 
                             mat Aj, 
                             mat p, 
                             bool v = true);
                             
        static int** makeMatrix(int n);
        
        static int findSolutions(vector<mat>& matrix, mat coeffs);
        
        static mat supTriangle(int n);
        
    public:
        
        static int solve(int**& m, 
                         vector<double>& prob, 
                         double* time,
                         char* inputPath, 
                         bool v);
        
        //! 
        /*! The inequation is in the form of A0 + A[i,j]*X[i,j] >= 0.
         *
         * \param 
         * \return
         */
        static int solve(int**& m, 
                         vector<double>& prob,
                         double* time,
                         vector<vector<int>> clauses,
                         bool v = true);
};

#endif
