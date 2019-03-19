#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int size_file(FILE *f); //return the number of rows/columns of the file
void file_to_matrix(FILE *f, float **m, unsigned int size); //copies the content of the file into the matrix
float determinant(float **m, unsigned int size); //calculates the determinant of m
void inverse(float **m, float **inverse, unsigned int size, float d); //gives the inverse by calculating the matrix of cofactors, taking the transpose and multiplying by 1/d (d is the determinant)
void matrix_to_file(float **m, unsigned int size); //write the content of the matrix into a file
unsigned int test_inversion(float **m, float **inv, unsigned int size); //used to test whether the inversion is ok or not

int cof_method(FILE *file, double **mat, unsigned int size)
{
    int i, j;
    float det;
    float **inv; //inverse matrix

    file = fopen("matrix.txt", "r");
    if (file == NULL) {printf("Couldn't open the file"); return 1;}


    size = size_file(file); //gets the number of elements in file
    rewind(file); //puts the cursor back to the beginning of the file

        /*******************
           Matrix creation
        ********************/

    mat = (float **) malloc(size * sizeof(float)); //creating a 1D array of 'size' elements of type float (these elements are pointers)
    inv = (float **) malloc( size * sizeof(float) );
    for (i=0; i<size; i++)
        mat[i] = (float *) malloc(size * sizeof(float)); //each element is also an array of 'size' elements of type float -> we get a 2D size*size matrix
    for (i=0; i<size; i++)
        inv[i] = (float *) malloc( size * sizeof(float) );

    file_to_matrix(file, mat, size); //fill the matrix
    fclose(file);

    det = determinant(mat, size); //get the determinant


    if (det == 0) {printf("The matrix cannot be inverted"); return 2;} //if non invertible stop
    else {inverse(mat, inv, size, det);} //calculate the inverse matrix

    if ( test_inversion(mat, inv, size) != 1 ) { matrix_to_file(inv, size); } //if ok put the matrix in a file
    else { printf("The matrix has not been properly inverted"); return 3;}

        /*****************
          Freeing memory
        ******************/

    for (i=0; i<size; i++)
        free(mat[i]);
    for (i=0; i<size; i++)
        free(inv[i]);
    free(mat);
    free(inv);
    return 0;
}

unsigned int size_file(FILE *f)
{
    unsigned int count = 0; //counting the number of elements (spaces not included)
    float numb; //the read number in the file

    while (fscanf(f, "%f", &numb) == 1) //while there's something
        count++;

    return sqrt(count);
}

float determinant(float **m, unsigned int size)
{
    unsigned int i, j, k, new_size, x, y; //x and y are the coordinates used to fill the cofactor matrix (when calculating the determinant)
    int sign;
    float det = 0; //determinant
    float **new_m; //cofactor matrix

    new_size = size - 1; //number of rows of the new matrix
    new_m = (float **) malloc( new_size * sizeof(float) ); //new matrix to calculate the determinant (methods with cofactors)
    for (j=0; j< new_size; j++)
        new_m[j] = (float *) malloc( new_size * sizeof(float) );

    if (size == 2) //if it's 2*2 use the formula ad-bc
        det = m[0][0] * m[1][1] - m[1][0] * m[0][1];
    else
    {
        for (i=0; i<size; i++) //develop along the 1st line (using cofactor method)
        {
            x = 0; //initialize x and y for each cofactor
            y = 0;

            if (i%2 == 0) {sign = 1;} //sign before the cofactor (+ if even, - if odd)
            else {sign = -1;}

            for (j=0; j< size; j++) //go through the m matrix
            {
                for (k=0; k<size; k++)
                {
                    if (j != 0 && k != i) //if not in the 1st line and ith column
                    {
                        if (y < new_size) {new_m[x][y] = m[j][k]; y++;} //complete first the line (column by column, same line)
                        else {x++; y = 0; new_m[x][y] = m[j][k]; y++;} //if the line is full, increase the line number and fill the first case
                    }
                }
            } //this routine allows us to create the cofactor matrices to derive the determinant
            det += sign * m[0][i] * determinant(new_m, new_size); //sum all the cofactors * the sign * the [1,i] element of m
        }
    }

    for (i=0; i<new_size; i++) //freeing the allocated memory
        free(new_m[i]);
    free(new_m);
    return det;
}

void file_to_matrix(FILE *f, float **m, unsigned int size)
{
    unsigned int i, j;
    float numb;

    for (i=0; i<size; i++)
    {
        for (j=0; j<size; j++)
        {
            fscanf(f, "%f", &numb); //read the content as a float
            m[i][j] = numb;
        }
    }
}

void inverse(float **m, float **inverse, unsigned int size, float d)
{
    unsigned int i, j, k, l, new_size, x, y;
    int sign;
    float mem;
    float **cof; //cofactor matrix (used to calculate the cofactor)

    new_size = size - 1; //number of rows/columns of cof
    cof = (float **) malloc( new_size * sizeof(float) );
    for (j=0; j< new_size; j++)
        cof[j] = (float *) malloc( new_size * sizeof(float) );

    if (size == 2) //if 2x2 use the formula
    {
        for (i=0; i<size; i++)
        {
            for (j=0; j<size; j++)
            {
                inverse[0][0] = m[1][1] / d;
                inverse[1][1] = m[0][0] / d;
                inverse[0][1] = - m[0][1] / d;
                inverse[1][0] = - m[1][0] / d;
            }
        }
    }
    else //if not derive the cofactors
    {
        for (i=0; i<size; i++) //this loop is used to fill the inverse matrix
        {
            for (j=0; j<size; j++) //go through the matrix (i,j the coordinates of the inverse matrix)
            {
                x = 0; //initialize x and y for each cofactor
                y = 0;

                if ( (i+j) %2 == 0 ) {sign = 1;} //sign before the cofactor
                else {sign = -1;}

                for (l=0; l< size; l++) //this loop is used to fill the comatrix
                {
                    for (k=0; k<size; k++) //go through the matrix (l,k the coordinates of the m matrix)
                    {
                        if (l != i && k != j) //if not in the ith line and jth column
                        {
                            if (y < new_size) {cof[x][y] = m[l][k]; y++;} //complete first the line (column by column, same line)
                            else {x++; y = 0; cof[x][y] = m[l][k]; y++;} //if the line is full, increase the line number and fill the first case
                        }
                    }
                }
                inverse[j][i] = sign * determinant(cof, new_size) / d; //fill the j,i element of the inverse matrix (j,i because it's transposed)
            }
        }
    }

    for (j=0; j<new_size; j++) //freeing memory
        free(cof[j]);
    free(cof);

}

void matrix_to_file(float **m, unsigned int size)
{
    unsigned int i,j;
    FILE *f;

    f = fopen("inverse.txt", "w");

    for (i=0; i<size; i++)
    {
        for (j=0; j<size; j++)
        {
            fprintf(f, "%f ", m[i][j]);
            if (j == size-1) { fprintf(f, "\n"); }
        }
    }
    fclose(f);
}

unsigned int test_inversion(float **m, float **inv, unsigned int size)
{
    unsigned int i, j, l, k;
    float res;

    for (i=0; i<size; i++)
        for (j=0; j<size; j++) //for each element
            {
                res = 0;
                for (l=0; l<size; l++)
                    res += inv[i][l] * m[l][j]; //derive the result of the product for each element
                if ( (i == j && abs(res - 1) > 0.001) || (i != j && abs(res) > 0.001) ) //if the identity (up to a certain accuracy, here 0.001, because elements are floats)
                        return 1; //return 1 (error)
            }
}
