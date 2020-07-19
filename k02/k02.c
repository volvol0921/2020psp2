#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MU_A (170.8)
#define SIGMA_A (5.43)
#define MU_B (169.7)
#define SIGMA_B (5.5)

extern double p_stdnorm(double z);

int main(void)
{
    double val;
    char fname[FILENAME_MAX];
    char buf[256];
    FILE* fp;
    double L1=1,L2=1;

    printf("input the filename of sample:");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1] = '\0';
    printf("the filename of sample: %s\n",fname);

    fp = fopen(fname,"r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        exit(EXIT_FAILURE);
    }

    while(fgets(buf,sizeof(buf),fp) != NULL){
        sscanf(buf,"%lf",&val);

        L1 *= p_stdnorm ((val - MU_A) / SIGMA_A);
        L2 *= p_stdnorm ((val - MU_B) / SIGMA_B);
    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }

    printf("L_A: %f\n",L1);
    printf("L_B: %f\n",L2);

    return 0;


}

double p_stdnorm(double z)
{
    return 1/sqrt(2*M_PI) * exp(-z*z/2);
}

