#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <math.h>
#define PI 3.14159265359

void boundaries(float *xN, float *yN, float *step, float *accuracy);
void set_grid(gsl_matrix *m, int size_x, int size_y, float step);
void update(gsl_matrix *m, int size_x, int size_y, float accuracy);
float average_4_points(double A, double B, double C, double D);
void write_file(gsl_matrix *m, int size_x, int size_y);

int main()
{
    float xN, yN, step, accuracy;
    int size_x, size_y, i, j;
    gsl_matrix *m;

    boundaries(&xN, &yN, &step, &accuracy);
    size_x = (int) xN/step+1; //dimensions of the matrix (size_x number of columns, size_y number of lines)
    size_y = (int) yN/step+1;

    m = gsl_matrix_calloc(size_y, size_x);
    set_grid(m, size_x, size_y, step);

    update(m, size_x, size_y, accuracy);

    write_file(m, size_x, size_y);

    gsl_matrix_free(m);

}

void boundaries(float *xN, float *yN, float *step, float *accuracy)
{
    printf("Boundaries : [0, xN], [0, yN]\n");
    printf("xN ?\n");
    scanf("%f", xN);

    printf("yN ?\n");
    scanf("%f", yN);

    printf("Step ?\n");
    scanf("%f", step);

    printf("Accuracy ?\n");
    scanf("%f", accuracy);
}

void set_grid(gsl_matrix *m, int size_x, int size_y, float step)
{
    unsigned int i,j;

    gsl_matrix_set_all(m, 1);
/*
    for (i=0; i<size_y; i++) //0 on the sides (does not have any solution)
        for (j=0; j<size_x; j++)
            if (i==0 || j==0 || i==size_y-1 || j==size_x-1)
                gsl_matrix_set(m, i, j, 0);
*/

    for (i=0; i<size_y; i++) //0 on the sides and sin(PI*x/Lx) on the top one (Lx end point of the interval [0,Lx], not the length)
        for (j=0; j<size_x; j++) //analytic solution prop to sin kx * sinh ky
        {
            if (i==0 || j==0 || j==size_x - 1)
                gsl_matrix_set(m, i, j, 0); //0 on the side except the top one
            else if (i==size_y - 1)
                gsl_matrix_set(m, i, j, sin(PI * (float) j / (size_x - 1))); // sin(PI*x/Lx)
        }

}

void update(gsl_matrix *m, int size_x, int size_y, float accuracy)
{
    unsigned int i,j;
    double d, l, r, u, res, value;
    gsl_vector *v;
    gsl_matrix *check;

    check = gsl_matrix_calloc(size_y -2, size_x -2); //matrix to know which element has reached its value
    gsl_matrix_set_all(check, 1);
    v = gsl_vector_calloc(size_x);

    while (gsl_matrix_isnull(check) != 1)
    {
        gsl_matrix_set_all(check, 1);
        gsl_matrix_get_row(v, m, 0);
        for (i=1; i<size_y-1; i++)
        {
            gsl_vector_set(v, 0, gsl_matrix_get(m,i,0));
            for (j=1; j<size_x-1; j++)
            {
                res = gsl_matrix_get(m, i, j); //previous value
                d = gsl_vector_get(v, j); //down point
                l = gsl_vector_get(v, j-1); //left point
                u = gsl_matrix_get(m, i+1, j); //up point
                r = gsl_matrix_get(m, i, j+1); //right point
                value = average_4_points(u, d, l, r);// new value

                gsl_matrix_set(m, i, j, value);
                gsl_vector_set(v, j, res);

                if (fabs(res - value) < accuracy )
                    gsl_matrix_set(check, i-1, j-1, 0);
            }
        }
    }

    gsl_vector_free(v);
    gsl_matrix_free(check);
}

float average_4_points(double A, double B, double C, double D)
{
    return((A+B+C+D)/4);
}

void write_file(gsl_matrix *m, int size_x, int size_y)
{
    unsigned int i, j;
    FILE *f;

    f = fopen("sol.txt", "w");

    for (i=0; i<size_y; i++)
        {
            for (j=0; j<size_x; j++)
                fprintf(f, "%g ", gsl_matrix_get(m, i, j));
            fprintf(f, "\n");
        }

    fclose(f);
}
