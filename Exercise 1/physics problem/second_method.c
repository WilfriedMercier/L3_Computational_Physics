#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_const_cgsm.h>

#define M 40 //mass in kg
#define G GSL_CONST_CGSM_GRAV_ACCEL //g in N/kg
#define W1 (M*G) //weight in N (orientated)
#define B 80 //distance between the attachment points and the centre of the equilateral triangle
#define A (sqrt(3)*B)
#define C (3*B/2)
#define PI 3.14159265359

void init(gsl_vector *M1, gsl_vector *M2, gsl_vector *M3, double x, double y);
void compute_angles(gsl_vector *M1, gsl_vector *M2, gsl_vector *M3, double *t1, double *t2, double *t3, double *p1, double *p2, double *p3);
void matrix_fill(gsl_matrix *m, double t1, double t2, double t3, double p1, double p2, double p3);
int check(gsl_matrix *, gsl_vector *v);

void second_method()
{
    int res, s;
    double i,j;
    double theta1, theta2, theta3, phi1, phi2, phi3;
    gsl_vector  *M1M, *M2M, *M3M, *sol, *W;
    //W is weight vector, sol the solution
    gsl_matrix *m, *m_copy; //m the matrix in the linear system
    gsl_permutation *perm;

    FILE *f;

    f = fopen("problem2.txt", "w");
    fprintf(f, "x y R1 R2 R3\n");

    M1M = gsl_vector_calloc(3); //position vectors
    M2M = gsl_vector_calloc(3);
    M3M = gsl_vector_calloc(3);

    W = gsl_vector_calloc(3);
    sol = gsl_vector_calloc(3);
    m = gsl_matrix_calloc(3,3);
    m_copy = gsl_matrix_calloc(3,3);

    perm = gsl_permutation_calloc(3);

    gsl_vector_set(W, 2, W1); //define the weight vector W along the z axis

    for (i=0; i<A; i+=0.5)
    {
        for (j=0; j<C; j+=0.5)
        {
            init(M1M, M2M,M3M,i,j);
            compute_angles(M1M, M2M, M3M, &theta1, &theta2, &theta3, &phi1, &phi2, &phi3);
            matrix_fill(m, theta1, theta2, theta3, phi1, phi2, phi3);
            gsl_matrix_memcpy(m_copy, m);

            gsl_linalg_LU_decomp(m, perm, &s);
            gsl_linalg_LU_solve(m, perm, W, sol); //solve linear system

            res = check(m_copy, sol);
            if (res == 1) {printf("e1 %d %d %f %f %f %f %f %f\n", i, j, theta1, theta2,  theta3, phi1, phi2, phi3);}
            if (res == 2) {printf("e2 %d %d %f %f %f %f %f %f\n", i, j, theta1, theta2, theta3, phi1, phi2, phi3);}
            if (res == 3) {printf("e3 %d %d %f %f %f %f %f %f\n", i, j, theta1, theta2, theta3, phi1, phi2, phi3);}

            if (gsl_vector_get(sol, 0)>0 && gsl_vector_get(sol, 1)>0 && gsl_vector_get(sol, 2)>0)
            {
            fprintf(f, "%f %f", i, j);
            fprintf(f, " %f", gsl_vector_get(sol, 0));
            fprintf(f, " %f", gsl_vector_get(sol, 1));
            fprintf(f, " %f\n", gsl_vector_get(sol, 2));}
            else{fprintf(f, "%f %f NaN NaN NaN\n", i, j);}

            gsl_matrix_set_zero(m); //need to empty them to avoid issues
            gsl_matrix_set_zero(m_copy);
            gsl_vector_set_zero(sol);
            gsl_vector_set_zero(M1M);
            gsl_vector_set_zero(M2M);
            gsl_vector_set_zero(M3M);
        }
        printf("%f\n", i);
    }

    fclose(f);

    gsl_vector_free(M1M);
    gsl_vector_free(M2M);
    gsl_vector_free(M3M);
    gsl_vector_free(W);
    gsl_vector_free(sol);
    gsl_matrix_free(m);
    gsl_matrix_free(m_copy);
    gsl_permutation_free(perm);
}

void init(gsl_vector *M1M, gsl_vector *M2M, gsl_vector *M3M, double x, double y)
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

void compute_angles(gsl_vector *M1, gsl_vector *M2, gsl_vector *M3, double *t1, double *t2, double *t3, double *p1, double *p2, double *p3)
{
    double r1, r2, r3;

    r1 = sqrt(pow(gsl_vector_get(M1,0),2) + pow(gsl_vector_get(M1,1),2) + pow(gsl_vector_get(M1,2),2));
    r2 = sqrt(pow(gsl_vector_get(M2,0),2) + pow(gsl_vector_get(M2,1),2) + pow(gsl_vector_get(M2,2),2));
    r3 = sqrt(pow(gsl_vector_get(M3,0),2) + pow(gsl_vector_get(M3,1),2) + pow(gsl_vector_get(M3,2),2));

    *t1 = acos(-gsl_vector_get(M1,2)/r1);
    *t2 = acos(-gsl_vector_get(M2,2)/r2);
    *t3 = acos(-gsl_vector_get(M3,2)/r3);

    *p1 = atan2(-gsl_vector_get(M1,1), -gsl_vector_get(M1,0));
    *p2 = atan2(-gsl_vector_get(M2,1), -gsl_vector_get(M2,0));
    *p3 = atan2(-gsl_vector_get(M3,1), -gsl_vector_get(M3,0));

    if (*p1 < 0)
        *p1 += 2*PI;
    if (*p2 <0)
        *p2 += 2*PI;
    if (*p3 < 0)
        *p3 += 2*PI;
}

void matrix_fill(gsl_matrix *m, double t1, double t2, double t3, double p1, double p2, double p3)
{
    gsl_matrix_set(m, 0, 0, cos(t1) * cos(p1));
    gsl_matrix_set(m, 0, 1, cos(t2) * cos(p2));
    gsl_matrix_set(m, 0, 2, cos(t3) * cos(p3));
    gsl_matrix_set(m, 1, 0, cos(t1) * sin(p1));
    gsl_matrix_set(m, 1, 1, cos(t2) * sin(p2));
    gsl_matrix_set(m, 1, 2, cos(t3) * sin(p3));
    gsl_matrix_set(m, 2, 0, sin(t1));
    gsl_matrix_set(m, 2, 1, sin(t2));
    gsl_matrix_set(m, 2, 2, sin(t3));
}

int check(gsl_matrix *m, gsl_vector *v)
{
    unsigned int i,j;
    double sum;

    for (i=0; i<3; i++)
    {
        sum = 0;
        for (j=0; j<3; j++)
        {
            sum += gsl_matrix_get(m,i,j) * gsl_vector_get(v, j);
        }
        if (i==0 && abs(sum) > 0.01)
            {gsl_matrix_fprintf(stdout,m,"%g");return 1;}
        if (i==1 && abs(sum) > 0.01)
            return 2;
        if (i==2 && abs(sum - W1) > 0.01)
            return 3;
    }
    return 0;
}
