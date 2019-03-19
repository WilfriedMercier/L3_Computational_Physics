#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#define L 10
#define BACKMEAN 5.8
#define BACKDEV 0.4
#define N 50000

double Gauss();//routine for generating a gaussian background signal

int main()
{
    unsigned int i, count; //count is counting the number of numbers with k>5
    float signal = 0, lambda, k, back; //lambda is the total mean, k is the poisson random number, back is the background signal (gaussian)

    const gsl_rng_type *t; //type generator
    gsl_rng *r; //random number

    gsl_rng_env_setup();//set up environment

    t = gsl_rng_default;
    r = gsl_rng_alloc(t);

    do
    {
        count = 0;

        for (i=0; i<N; i++)
        {
            //back = BACKMEAN; //if no gaussian error
            back = Gauss(); //if gaussian error
            lambda = back + signal; //overall signal
            k = gsl_ran_poisson(r, lambda); //generate poisson

            if (k>=5)
                count++;
        }
        signal += 0.1; //increase the signal
    }while( (float) count/N < 0.95); //do until the confidence level is not met

    printf("%f %f", (float) count/N, (float) (signal-0.1)/10);

    gsl_rng_free(r); //free memory

    return 0;
}

double Gauss()
{
    double res;
    const gsl_rng_type *t; //type generator
    gsl_rng *r; //random number

    gsl_rng_env_setup();//set up environment

    t = gsl_rng_default;
    r = gsl_rng_alloc(t);

    res = BACKMEAN + gsl_ran_gaussian(r, BACKDEV); //generate a gaussian signal with mean BACKMEAN and deviation BACKDEV
    gsl_rng_free(r);

    return res;
}
