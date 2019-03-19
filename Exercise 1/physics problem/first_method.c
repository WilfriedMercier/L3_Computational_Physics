#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_const_cgsm.h>

#define M 40 //mass in kg
#define G GSL_CONST_CGSM_GRAV_ACCEL //g in N/kg
#define W1 (-M*G) //weight in N (orientated)
#define B 80 //distance between the attachment points and the centre of the equilateral triangle
#define A (sqrt(3)*B)
#define C (3*B/2)

void initialize(gsl_vector *M1, gsl_vector *M2, gsl_vector *M3, double x, double y);
void vec_prod(gsl_vector *in1, gsl_vector *in2, gsl_vector *out);
void fill_vector(gsl_vector *out, gsl_vector *M1M, gsl_vector *M2M, gsl_vector *M3M, gsl_vector *W);
void fill_matrix(gsl_matrix *out, gsl_vector *M1M, gsl_vector *M2M, gsl_vector *M3M);
void fill_m_moments(gsl_matrix *out, gsl_vector *MiM, int sign, unsigned int line, unsigned int col);
void fill_m_force(gsl_matrix *out, int sign, unsigned int line, unsigned int col);

/*****************
initialize :
    input : 3 position vectors M1M, M2M, M3M labelled M1, M2 and M3 in the function + position of M(x,y)
    goal : computes M1M, M2M, M3M

vec_prod :
    input : 2 vectors in1 and in2
    output : 1 vector
    goal : compute the cross prod of in1 and in2

fill_vector :
    input : 3 position vectors + weight vector
    output : a 18D vector labelled out
    goal : fill the constant vector in the linear system of equations

fill_matrix:
    input : 3 position vectors
    output : the 18x18 matrix called out
    goal : fill the matrix in the linear system

fill_m_moments:
    input : 1 position vector + sign (1 or -1) + line and column of the 1st component of vector Rij in the moment equation
    output : the 18x18 matrix
    goal : fill 3 lines of the matrix corresponding to the moments equations

fill_m_force:
    input : sign (1 or -1) + line and column of the 1st component of vector Rij
    output : the 18x18 matrix
    goal : fill 3 lines of the matrix corresponding to the force equations
******************/

int first_method()
{
    double R1, R2, R3, i, j;
    unsigned int k;
    int s;
    gsl_vector  *M1M, *M2M, *M3M, *cte, *sol, *W;
    //W is weight vector, cte the cte vector in the linear system, sol the solution
    gsl_matrix *m; //m the matrix in the linear system
    gsl_permutation *perm;

    FILE *f;

    f = fopen("problem.txt", "w");
    fprintf(f, "x y R1 R2 R3\n");

    cte = gsl_vector_calloc(18);
    sol = gsl_vector_calloc(18);
    W = gsl_vector_calloc(18);
    m = gsl_matrix_calloc(18,18);

    M1M = gsl_vector_calloc(3); //position vectors
    M2M = gsl_vector_calloc(3);
    M3M = gsl_vector_calloc(3);

    perm = gsl_permutation_calloc(18);

    gsl_vector_set(W, 2, W1); //define the weight vector W along the z axis

    for (i=0; i<A; i+=0.5)
    {
        printf("%f\n", i);
        for (j=0; j<C; j+=0.5)
        {
            initialize(M1M, M2M, M3M, i, j);
            fill_vector(cte, M1M, M2M, M3M, W);
            fill_matrix(m, M1M, M2M, M3M);

            gsl_linalg_LU_decomp(m, perm, &s);
            gsl_linalg_LU_solve(m, perm, cte, sol); //solve linear system

            R1 = sqrt( pow(gsl_vector_get(sol,9), 2) + pow(gsl_vector_get(sol, 10), 2) + pow(gsl_vector_get(sol, 11), 2));
            R2 = sqrt( pow(gsl_vector_get(sol,12), 2) + pow(gsl_vector_get(sol, 13), 2) + pow(gsl_vector_get(sol, 14), 2));
            R3 = sqrt( pow(gsl_vector_get(sol,15), 2) + pow(gsl_vector_get(sol, 16), 2) + pow(gsl_vector_get(sol, 17), 2));

            if (gsl_vector_get(sol, 0)>0 && gsl_vector_get(sol, 1)>0 && gsl_vector_get(sol, 2)>0)
            {
            fprintf(f, "%f %f", i, j);
            fprintf(f, " %f", R1);
            fprintf(f, " %f", R2);
            fprintf(f, " %f", R3);
            fprintf(f, "\n");
            }
            else{fprintf(f, "%f %f NaN NaN NaN\n", i, j);}

            gsl_matrix_set_zero(m); //need to empty them to avoid issues
            gsl_vector_set_zero(cte);
            gsl_vector_set_zero(sol);
            gsl_vector_set_zero(M1M);
            gsl_vector_set_zero(M2M);
            gsl_vector_set_zero(M3M);
        }
    }

    fclose(f);

    gsl_vector_free(M1M);
    gsl_vector_free(M2M);
    gsl_vector_free(M3M);
    gsl_vector_free(W);
    gsl_vector_free(cte);
    gsl_vector_free(sol);
    gsl_matrix_free(m);
    gsl_permutation_free(perm);
    return 0;
}

void initialize(gsl_vector *M1M, gsl_vector *M2M, gsl_vector *M3M, double x, double y)
{
    gsl_vector_set(M1M, 0, x);
    gsl_vector_set(M1M, 1, y-C);
    gsl_vector_set(M1M, 2, -10);

    gsl_vector_set(M2M, 0, x-A);
    gsl_vector_set(M2M, 1, y-C);
    gsl_vector_set(M2M, 2, -10);

    gsl_vector_set(M3M, 0, x-A/2);
    gsl_vector_set(M3M, 1, y);
    gsl_vector_set(M3M, 2, -10);
}

void vec_prod(gsl_vector *in1, gsl_vector *in2, gsl_vector *out)
{
    double x1 = gsl_vector_get(in1, 0);
    double y1 = gsl_vector_get(in1, 1);
    double z1 = gsl_vector_get(in1, 2);
    double x2 = gsl_vector_get(in2, 0);
    double y2 = gsl_vector_get(in2, 1);
    double z2 = gsl_vector_get(in2, 2);

    gsl_vector_set(out, 0, y1*z2 - z1*y2);
    gsl_vector_set(out, 1, x2*z1 - x1*z2);
    gsl_vector_set(out, 2, x1*y2 - x2*y1);
}

void fill_vector(gsl_vector *out, gsl_vector *M1M, gsl_vector *M2M, gsl_vector *M3M, gsl_vector *W)
{
    unsigned int i, count1 = 0, count2 = 0;
    gsl_vector *res;
    res = gsl_vector_calloc(3);

    for (i=0; i<18; i++)
    {
        if (count1 == 2)
        {
            gsl_vector_set(out, i, -W1); //if 3rd component put -mg
            if (count2 == 0)
                vec_prod(M1M, W, res); //calculate M1M x W
            else if (count2 == 1)
                vec_prod(M2M, W, res); //calculate M2M x W
            else
                vec_prod(M3M, W, res); //calculate M3M x W
            count2++;
        }
        else if ( count1 > 2)
        {
            gsl_vector_set(out, i, -gsl_vector_get(res, count1 - 3)); //put the ith component of the cross product
        }
        count1++;
        if (count1 == 6) {count1=0;}
    }
    gsl_vector_free(res);
}

void fill_matrix(gsl_matrix *out, gsl_vector *M1M, gsl_vector *M2M, gsl_vector *M3M)
{
    fill_m_force(out, 1, 0, 9); //1st to 3rd lines of the matrix
    fill_m_force(out, -1, 0, 0);
    fill_m_force(out, -1, 0, 6);

    fill_m_moments(out, M1M, -1, 3, 0); //4th to 6th
    fill_m_moments(out, M1M, -1, 3, 6);

    fill_m_force(out, 1, 6, 12); //7th to 9th
    fill_m_force(out, 1, 6, 0);
    fill_m_force(out, 1, 6, 3);

    fill_m_moments(out, M2M, 1, 9, 0); //10th to 12th
    fill_m_moments(out, M2M, 1, 9, 3);

    fill_m_force(out, 1, 12, 15); //13th to 15th
    fill_m_force(out, 1, 12, 6);
    fill_m_force(out, -1, 12, 3);

    fill_m_moments(out, M3M, 1, 15, 6); //16th to 18th
    fill_m_moments(out, M3M, -1, 15, 3);
}

void fill_m_force(gsl_matrix *out, int sign, unsigned int line, unsigned int col)
{
    unsigned int i;
    for (i=0; i<3; i++)
    {
        gsl_matrix_set(out, line + i, col + i, sign);
    }
}

void fill_m_moments(gsl_matrix *out, gsl_vector *MiM, int sign, unsigned int line, unsigned int col)
{
    gsl_matrix_set(out, line, col + 2, sign*gsl_vector_get(MiM, 1));
    gsl_matrix_set(out, line, col + 1, -sign*gsl_vector_get(MiM, 2));
    gsl_matrix_set(out, line + 1, col, sign*gsl_vector_get(MiM, 2));
    gsl_matrix_set(out, line + 1, col + 2, -sign*gsl_vector_get(MiM, 0));
    gsl_matrix_set(out, line + 2, col + 1, sign*gsl_vector_get(MiM, 0));
    gsl_matrix_set(out, line + 2, col, -sign*gsl_vector_get(MiM, 1));
}




