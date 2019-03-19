#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_permutation.h>

#define L 0.5 //m
#define TOUT 0 //degrees
#define TFUR 1000 //degrees
#define K 59 //W/m/K
#define C 450 //J/kg/K
#define RHO 7900 //kg/m^3
#define ACC 0.1


void set_vector(gsl_vector *v, unsigned int N);
void set_matrix(gsl_matrix *m, float h, float dt, unsigned int N, const float A);


int main()
{
    const float A = (float) K/(RHO*C); //m^2/s
    unsigned int i, check = 0;
    unsigned int N_points = 500;
    int sign;
    float spatial_step = L/(N_points-1);
    //float time_step = (spatial_step*spatial_step)/(4*A); //s
    float time_step = 1; //s

    FILE *f;

    f = fopen("Temp0bis.txt", "w");

    gsl_vector *v, *x; //v vector at time t, x vector after solving the system (time t+1), c is used to check convergence
    gsl_matrix *m;
    gsl_permutation *p;

    v = gsl_vector_calloc(N_points);
    x = gsl_vector_calloc(N_points);
    m = gsl_matrix_calloc(N_points,N_points);
    p = gsl_permutation_calloc(N_points);

    set_vector(v, N_points);
    set_matrix(m, spatial_step, time_step, N_points, A);
    gsl_linalg_LU_decomp(m, p, &sign); //LU decomposition (only needs to be done once since the matrix is always the same)

    for (i=0; i<N_points; i++)
        {
            fprintf(f, "%g ", gsl_vector_get(v, i));
        }
        fprintf(f, "\n");

    while (check != N_points) //if check = N (i.e. all points are accurate enough) end the loop
    {
        check = 0;
        gsl_linalg_LU_solve(m, p, v, x); //solution in x

        for (i=0; i<N_points; i++) //if accurate enough increase check by 1
        {
            fprintf(f, "%g ", gsl_vector_get(x, i));

            if ((fabs(gsl_vector_get(v, i) - gsl_vector_get(x, i)) < ACC))
                check++;
        }
        fprintf(f, "\n");

        gsl_vector_memcpy(v, x); //copy solution to v
    }

    fclose(f);

    gsl_vector_free(v);
    gsl_vector_free(x);
    gsl_matrix_free(m);
    gsl_permutation_free(p);
}

void set_vector(gsl_vector *v, unsigned int N)
{
    gsl_vector_set_all(v, 20);
    gsl_vector_set(v, N-1, TOUT);
    gsl_vector_set(v, 0, TFUR);
}

void set_matrix(gsl_matrix *m, float h, float dt, unsigned int N, const float A)
{
    unsigned int i,j;
    float a, b;

    a = -A*dt/(h*h); //-(alpha*dt)/h^2
    b = 1 - 2 * a; //1 + 2*(alpha*dt)/h^2

    for (i=0; i<N; i++)
        for (j=0; j<N; j++)
        {
            if ((i==0 && j==0) || (i==N-1 && j == N-1)) //if first or last element
                gsl_matrix_set(m, i, j, 1); //put 1
            else if (j == i-1 && i!=N-1) //fill the column as expected (j position of the first non zero element) + do not fill the last line
            {
                gsl_matrix_set(m, i, j, a);
                gsl_matrix_set(m, i, j+1, b);
                gsl_matrix_set(m, i, j+2, a);
            }
        }
}

