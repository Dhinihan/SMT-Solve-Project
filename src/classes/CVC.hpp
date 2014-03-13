#ifndef CVC_H
#define CVC_H

#include "Matrix.hpp"

/*  Class CVC
 *  
 *  A static class to create the CVC file.
 */
class CVC
{
    private:
        /*Cannot create instaces*/
        CVC();
        
    public:
        /* Method createFile: create an input for cvc4.
         *
         * parameter M       : the Matrix with the coeffitients.
         * parameter fileName: the name of the file to be created
         */
        static void createFile(Matrix* M, const char* fileName);   
};

#endif
