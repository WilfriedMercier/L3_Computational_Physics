#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <math.h>
#define PI 3.14159265359

void first(); //algebrical inversion
void second(); //rejection technique

int main()
{
    //first();
    second();
    return 0;
}

void first()
{
    const gsl_rng_type *t; //type of the generator
    gsl_rng *r; //random number

    unsigned int i;
    double val;
    FILE *f;

    f = fopen("sin_1_100000.txt", "w");
    gsl_rng_env_setup(); //set the random generator

    t = gsl_rng_default; //set type to uniform ([0,1])
    r = gsl_rng_alloc(t);

    for (i=0; i<100000; i++)
    {
        val = acos(2*gsl_rng_uniform(r)-1); //x = arccos(G) = arccos(2*F-1) where F is between 0 and 1 (G between -1 and +1)
        fprintf(f, "%f\n", val);
    }

    fclose(f);
    gsl_rng_free(r); //free memory
}

void second()
{
    const gsl_rng_type *t; //type generator
    gsl_rng *r; //random number

    unsigned int i;
    double x, y;
    FILE *f;

    f = fopen("sin_2_100000.txt", "w");
    gsl_rng_env_setup();//set up environment

    t = gsl_rng_default;
    r = gsl_rng_alloc(t);

    for (i=0; i<100000; i++)
    {
        x = PI*gsl_rng_uniform(r); //generate the random number between 0 and +PI
        y = gsl_rng_uniform(r); //generate the y coordinate of the point (x,y)
        if (y < sin(x)) //check it lies under the curve g(x)
            fprintf(f, "%f\n", x);
    }

    fclose(f);
    gsl_rng_free(r); //free memory
}
