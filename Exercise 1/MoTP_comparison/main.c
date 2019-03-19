#include "main.h"
#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_linalg.h>

void f_to_matrix(FILE *f, FILE *c, gsl_matrix *gslm, gsl_vector *b, unsigned int size); //copies the content of the file into the matrix
void LU(gsl_matrix *gslm, gsl_vector *b, gsl_vector *x, unsigned int size); //LU method
int check(gsl_matrix *gslm, gsl_vector *x, gsl_vector *b, unsigned int size); //checking whether the solution is good
void SVD(gsl_matrix *gslm, gsl_vector *b, gsl_vector *x, unsigned int size); //SVD method
void solution(float **m, gsl_vector *b, unsigned int size);

int main()
{
    unsigned int size;
    int ret;

    gsl_vector *gsl_x, *gsl_b; //x is the vector to be found and b the constant vector on the right of the equality
    gsl_matrix *gsl_m, *gsl_m_copy; //matrix for LU and SVD methods

        /*****************
           Files creation
        ******************/

    FILE *f, *c; //f is the matrix, c the constant vector

    f = fopen("matrix.txt", "r");
    c = fopen("const_vec.txt", "r");

    size = size_file(f); //getting the size
    rewind(f); //puts the cursor back to the beginning of the file

        /****************************
           Matrix and vector creation
        *****************************/

    gsl_m = gsl_matrix_calloc(size, size);//allocating memory
    gsl_m_copy = gsl_matrix_calloc(size, size);
    gsl_x = gsl_vector_calloc(size);
    gsl_b = gsl_vector_calloc(size);

    gsl_matrix_fscanf(f, gsl_m); //getting the values into the matrix and the vector
    gsl_vector_fscanf(c, gsl_b);

    fclose(f);
    fclose(c);

    gsl_matrix_memcpy(gsl_m_copy, gsl_m); //copying the matrix before it's overwritten

        /****************************
           LU and SVD solutions
        *****************************/

    LU(gsl_m, gsl_b, gsl_x, size);
    //SVD(gsl_m,gsl_b,gsl_x,size);

    ret = check(gsl_m_copy, gsl_x, gsl_b, size); //checking whether the solution is fine
    if ( ret == 1 ) { printf("The solution is not correct"); }
    else {printf("Correct solution : \n"); gsl_vector_fprintf(stdout, gsl_x, "%g");}

    gsl_matrix_free(gsl_m);//freeing memory
    gsl_matrix_free(gsl_m_copy);
    gsl_vector_free(gsl_x);
    gsl_vector_free(gsl_b);
    return 0;
}

void LU(gsl_matrix *gslm, gsl_vector *b, gsl_vector *x, unsigned int size)
{
    int s;
    gsl_permutation *permut;

    permut = gsl_permutation_alloc(size);

    gsl_linalg_LU_decomp(gslm, permut, &s);
    gsl_linalg_LU_solve(gslm, permut, b, x);

    gsl_permutation_free(permut);
}

void SVD(gsl_matrix *gslm, gsl_vector *b, gsl_vector *x, unsigned int size)
{
    gsl_matrix *V; //the matrix in A = UDV
    gsl_vector *work, *D; //the vector in A = UDV

    V = gsl_matrix_calloc(size, size); //allocating memory (putting 0 everywhere)
    D = gsl_vector_calloc(size);
    work = gsl_vector_calloc(size);

    gsl_linalg_SV_decomp(gslm, V, D, work);
    gsl_linalg_SV_solve(gslm, V, D, b, x);

    gsl_matrix_free(V);
    gsl_vector_free(D);
    gsl_vector_free(work);
}

int check(gsl_matrix *gslm, gsl_vector *x, gsl_vector *b, unsigned int size)
{
    unsigned int i,j;
    float sum;
    gsl_vector *sol = gsl_vector_alloc(size);

    for (i=0; i<size; i++)
    {
        sum = 0;
        for (j=0; j<size; j++)
            {
                sum += gsl_matrix_get(gslm, i, j) * gsl_vector_get(x, j);
            }
        gsl_vector_set(sol, i, sum);
        if ( abs(sum - gsl_vector_get(b, i) > 0.001) )
            return 1;
    }
    gsl_vector_free(sol);
    return 0;
}

void solution(float **m, gsl_vector *b, unsigned int size)
{
    int i, j;
    float res;

    printf("The solution is:\n");
    for (i=0; i<size; i++)
        {
            res = 0;
            for (j=0; j<size; j++)
                res += m[i][j] * gsl_vector_get(b, j);
            printf("%f\n", res);
        }
}
