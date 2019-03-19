#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>

#define V 2000 //speed of the nuclei (m/s)
#define D 2 //initial distance between the nuclei and the screen (m)
#define T ((float) D/V) //time allowed for the nuclei to emit a photon before crossing the screen (s)
#define TAU (520*pow(10,-6)) //mean life time (s)
#define N 1000000 //number of nuclei at t=0
#define PI 3.14159265359
#define ACCX 0.1 //the accuracy of the detector in x
#define ACCY 0.3 //the same in y

void rejection(); //rejection technique

int main()
{
    rejection();
    return 0;
}


void rejection()
{
    const gsl_rng_type *t; //type generator
    gsl_rng *r; //random number

    unsigned int i;
    double time, y, theta, phi, err_x, err_y, pos_y;
    FILE *f;

    f = fopen("2D_corrected.txt", "w");
    gsl_rng_env_setup();//set up environment

    t = gsl_rng_default;
    r = gsl_rng_alloc(t);

    for (i=0; i<N; i++)
    {
        time = T*gsl_rng_uniform(r); //generate the random number between 0 and T
        y = gsl_rng_uniform(r); //generate the y coordinate of the point (x,y)
        if (y < exp(-time/TAU)) //check it lies under the curve g(x)
        {
            theta = 2*PI*gsl_rng_uniform(r) - PI;
            phi = 2*PI*gsl_rng_uniform(r) - PI;

            if (fabs(theta) < PI/2 && fabs(phi) < PI/2)
            {
                do
                {
                    err_x = ACCX*gsl_rng_uniform(r) - ACCX/2; //generate error in x between -5cm and +5cm
                    pos_y = gsl_rng_uniform(r); //generate the y coordinate of the point (err_x,y)
                }while(pos_y > exp(-err_x*err_x/(2*ACCX*ACCX))); //generate an error until it lies under the Gaussian

                do
                {
                    err_y = ACCY*gsl_rng_uniform(r) - ACCY/2; //generate error in x between -15cm and +15cm
                    pos_y = gsl_rng_uniform(r); //generate the y coordinate of the point (err_y,y)
                }while(pos_y > exp(-err_y*err_y/(2*ACCY*ACCY))); //generate an error until it lies under the Gaussian

                fprintf(f, "%f %f\n", (D - V*time)*tan(phi) + err_x, (D - V*time)*tan(theta) + err_y); //put the x and y coordinates in the file corrected with the error
            }

        }
    }

    fclose(f);
    gsl_rng_free(r); //free memory
}
