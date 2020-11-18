#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

// Binary Genetic Algorithm
// 
// minimizes the objective function designated in ff
// Before beginning, set all the parameters in parts
// I, II, and III
// Haupt & Haupt
// 2003

int main()
{
    // __________________________________________________________________
    // I. Setup the GA

    char *ff = "testfunction";  // objective function
    int npar = 2;   // number of optimization variables

    // __________________________________________________________________
    // II. Stopping criteria

    int maxit = 100;    // max number of iterations
    int mincost = -9999999; // minimum cost

    // __________________________________________________________________
    // III. GA parameters

    int popsize = 16;   // set population size
    float mutrate = 0.15;   // set mutation rate
    float selection = 0.5;  // fraction of population kept

    int nbits = 8;  // number of bits in each parameter
    int Nt = npar * nbits;  // total number of bits in a chromosome

    int keep = floor(selection * popsize);  // population members that survive

    // __________________________________________________________________
    // Create the initial population

    int iga = 0;    // generation counter initialized

    int *pop = random(popsize, Nt);  // random population of 1s and 0s
    
    // TODO: IMPLEMENT GADECODE
    float *par = gadecode(pop, 0, 10, nbits);   // convert binary to continuous values
    
    // TODO: IMPLEMENT FEVAL
    float *cost = feval(ff, par);   // calculates population cost using ff
    // __________________________________________________________________
    // De aqui en adelante, nada esta implementado

    // [cost, ind] = sort(cost);    // min cost in element 1

    // par = par(ind,:);    // sorts population with lowest cost first
    // pop=pop(ind,:);

    // minc(1) = min(cost);     // minc contains min of population

    // meanc(1) = mean(cost);   // meanc contains mean of population
    
    // __________________________________________________________________
    // Iterate through generations

    while (iga < maxit)
    {
        iga =  iga + 1;     // increments generation counter
    }

    return 0;
}


int *random(int rows, int cols)
{
    // Generate a rows by cols matrix with 1s and 0s

    float r[rows][cols];
    srand(time(NULL));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            r[i][j] = rand() % 2;
        }
    }
    return r;
}

float *gadecode(int chrom[], int lo, int hi, int bits)
{
    // TODO: genetic algorithm decode function

    float M = rows(chrom);
    float N = cols(chrom);

    float npar = N/bits;    // number of variables

    // quant=(0.5.^[1:bits]’);     // quantization levels
    int *t_bits = create_array(bits);
    float *quant = element_wise_power(0.5, t_bits);

    // TODO
    // quant=quant/sum(quant);     // quantization levels normalized

    // ct=reshape(chrom’,bits,npar*M)’;    // each column contains one variable
    float *ct = reshape(transpose(chrom), bits, npar*M);    // not transposed yet

    // par=((ct*quant)*(hi-lo)+lo);    // DA conversion and unnormalize varaibles

    // f=reshape(par,npar,M)’;     // reassemble population
    float *f = reshape(par, npar, M);   // not transposed yet
    
    return f;
}

int rows(int arr[]) 
{
    return sizeof(arr) / sizeof(arr[0]);
}

int cols(int arr[]) 
{
    return sizeof(arr[0]) / sizeof(arr[0][0]);
}

int *transpose(int arr[]) 
{
    // Swap rows and cols

    int rows = rows(arr);
    int cols = cols(arr);

    int t[rows][cols];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            t[i][j] = arr[j][i];
        }
    }

    return t;
}

int *create_array(int size)
{
    // Create an array of size n filled with numbers from 1 to n.
    
    int v[size];
    for (int i = 0; i < size; i++)
    {
        v[i] = i;
    }
    
    return v;
}

float *element_wise_power(float x, float arr[])
{
    // Calculate the power of x to every element in the array.

    int size = sizeof(arr) / sizeof(arr[0]);
    float p[size];

    for (int i = 0; i < size; i++)
    {
        p[i] = pow(x, arr[i]);
    }

    return p;
}

float *reshape(float arr[], int rows, int cols)
{
    float r[rows][cols];

    int current_row = 0;
    int current_col = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; i < cols; i++)
        {
            r[i][j] = arr[current_row][current_col];
            current_col++;

            if (current_col == cols)
            {
                current_col = 0;
                ++current_row;
            }
        }
    }

    return r;
}