#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <math.h>
#define PI 3.14159265359
#define SIGMA pow(10,-9)
#define EPSILON (8.85418782 * pow(10,-12))

void boundaries(float *step, float *accuracy);
void set_grid(gsl_matrix *m, int size_x, int size_y, float step);
void set_boundaries(gsl_matrix *m, int size_x, int size_y, float step);
void update(gsl_matrix *m, int size_x, int size_y, float accuracy, float step);
float average_4_points(double A, double B, double C, double D);
void write_file(gsl_matrix *m, int size_x, int size_y);

int main()
{
    float xN=200, yN=20, step, accuracy;
    int size_x, size_y;
    gsl_matrix *m;

    boundaries(&step, &accuracy);
    size_x = (int) xN/step; //dimensions of the capacitor (size_x number of columns, size_y number of lines)
    size_y = yN/step;

    m = gsl_matrix_calloc(3*size_y, 3*size_x);
    set_grid(m, size_x, size_y, step);
    set_boundaries(m, size_x, size_y, step);
    update(m, size_x, size_y, accuracy, step);

    write_file(m, size_x, size_y);

    gsl_matrix_free(m);

}

void boundaries(float *step, float *accuracy)
{
    printf("Step ?\n");
    scanf("%f", step);

    printf("Accuracy ?\n");
    scanf("%f", accuracy);
}

void set_grid(gsl_matrix *m, int size_x, int size_y, float step)
{
    unsigned int i,j;

    gsl_matrix_set_all(m, 0);

    for (i=size_y; i<2*size_y; i++)
        for (j=size_x; j<2*size_x; j++)
            gsl_matrix_set(m, i, j, 1);
}

void set_boundaries(gsl_matrix *m, int size_x, int size_y, float step)
{
    unsigned int j;
    float V_d, V_u, cte = (SIGMA * step)/EPSILON;

    for (j=size_x; j<2*size_x; j++)
    {/*
        V_d = -cte + (gsl_matrix_get(m, size_y+2, j) + gsl_matrix_get(m, size_y-2, j))/2;
        V_u = cte + (gsl_matrix_get(m, 2*size_y+2, j) + gsl_matrix_get(m, 2*size_y-2, j))/2;

        gsl_matrix_set(m, size_y, j, V_d);
        gsl_matrix_set(m, 2*size_y, j, V_u);*/
        gsl_matrix_set(m, size_y, j, -100);
        gsl_matrix_set(m, 2*size_y, j, 100);
    }

    for (j=0; j<3*size_x; j++)
    {
        gsl_matrix_set(m, 0, j, -100);
        gsl_matrix_set(m, 3*size_y-1, j, 100);
    }
}

void update(gsl_matrix *m, int size_x, int size_y, float accuracy, float step)
{
    unsigned int i,j;
    double d, l, r, u, res, value;
    gsl_vector *v;
    gsl_matrix *check;

    check = gsl_matrix_calloc(3*size_y , 3*size_x); //matrix to know which element has reached its value
    gsl_matrix_set_all(check, 1); //initializes it

    v = gsl_vector_calloc(3*size_x);

    while (gsl_matrix_isnull(check) != 1) //check with 0 everywhere means each element has changed by less than accuracy
    {
        //set_boundaries(m, size_x, size_y, step); //determine the new boundaries

        gsl_matrix_set_all(check, 1); //reinitializes it each time the condition is not reached

        for (i=0; i<3*size_y; i++) //boundaries and interface to 0
        {
            for (j=0; j<3*size_x; j++)
            {
                if (j>=size_x && j<2*size_x && i==1)//set the interface to 0
                {
                    gsl_matrix_set(check, size_y, j, 0);
                    gsl_matrix_set(check, 2*size_y, j, 0);
                }
                else if (i==0 || i==3*size_y-1 || j==0 || j==3*size_x-1)
                    gsl_matrix_set(check, i, j, 0);
            }
        }

        gsl_matrix_get_row(v, m, 0);
        for (i=1; i<3*size_y-1; i++)
        {
            gsl_vector_set(v, 0, gsl_matrix_get(m, i, 0));
            for (j=1; j<3*size_x-1; j++)
            {
                res = gsl_matrix_get(m, i, j); //previous value
                if ( (j<size_x || j>=2*size_x) || //if on the sides of the capacitor
                     (j>=size_x && j<2*size_x && i != size_y && i !=2*size_y)) //if in the inner part but not on the conductors
                {
                    d = gsl_vector_get(v, j); //down point
                    u = gsl_matrix_get(m, i+1, j); //up point
                    l = gsl_vector_get(v, j-1); //left point
                    r = gsl_matrix_get(m, i, j+1); //right point

                    value = average_4_points(u, d, l, r);// new value
                    gsl_matrix_set(m, i, j, value); //put the new value

                    if (fabs(res - value) < accuracy ) //if accurate enough
                        gsl_matrix_set(check, i, j, 0); //put 0 in check
                }
                gsl_vector_set(v, j, res); //puts in v at position j the unmodified value
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
    unsigned int i,j;
    FILE *f;

    f = fopen("sol_200x20.txt", "w");

    for (i=0; i<3*size_y; i++)
    {
        for (j=0; j<3*size_x; j++)
            fprintf(f, "%g ", gsl_matrix_get(m, i, j));
        fprintf(f, "\n");
    }
    fclose(f);
}
