#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int count;

extern double ave_online(double val,double ave);

extern double var_online(double val, double ave, double square_ave);

int main(void)
{
    double val;
    char fname[FILENAME_MAX];
    char buf[256];
    double average = 0.0;
    double sq_average = 0.0;
    double variance = 0.0;
    FILE* fp;

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
        ++count;

        average = ave_online (val, average);
        variance = var_online (val, average, sq_average);
        sq_average = ave_online (val * val, sq_average);
    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }

    printf("SAMPLE DATE\n");
    printf ("Average: %lf\n", average);
    printf ("Variance: %lf\n", variance);
    printf("ESTIMATED DATE\n");
    printf ("Average: %lf\n", average);
    printf ("Variance: %lf\n", ((double)count / (count - 1)) * variance);

    fclose (fp);


    return 0;


}

double ave_online(double val,double ave){
    ave = (count - 1) * ave / count + val / count;
    return ave;
}

double var_online(double val, double ave, double square_ave){
    double var;
    square_ave = (count - 1) * square_ave / count + pow(val,2) / count;
    var = square_ave - pow(ave,2);

    return var;
}