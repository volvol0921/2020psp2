#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern void get_bound(int num_male, int num_whole, double* lower_bound, double* upper_bound);
extern int choose(int n, int r);

int main(void)
{
    double val;
    char fname[FILENAME_MAX];
    char buf[256];
    FILE* fp;
    int num_male, num_female, num_unknown, num_whole;
    int gender;
    double lower_bound,upper_bound;

    printf("input the filename of sample:");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1] = '\0';
    printf("the filename of sample: %s\n",fname);

    fp = fopen(fname,"r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        exit(EXIT_FAILURE);
    }

    num_male=num_female=num_unknown=0;
    while(fgets(buf,sizeof(buf),fp) != NULL){
        sscanf(buf,"%d,%lf",&gender, &val);
        if(gender==1){ num_male++;
        }else if(gender==2){ num_female++;
        }else{ num_unknown++;
        }
    }
    num_whole = num_male+num_female+num_unknown;

    printf("================================\n");
    printf("Number of male sample : %d\n",num_male);
    printf("Number of female sample : %d\n",num_female);
    printf("Male Ratio : %lf\n",(double)num_male/num_whole);

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }

    get_bound(num_male, num_whole, &lower_bound, &upper_bound);

    printf("Population Male Ratio (estimated) : %lf--%lf\n",lower_bound,upper_bound);
    printf("============================\n");

    return 0;

}

void get_bound(int num_male, int num_whole, double* lower_bound, double* upper_bound)
{
    double z;
    int n;
    
    z=0;
    n=0;
    while(z < 0.025){
        z += choose(num_whole,num_male) * pow((double)n/num_whole, num_male) * pow((double)(num_whole-n)/num_whole, num_whole-num_male); 
        printf("%lf\n",z);
        n ++; 
    }
    *lower_bound = (double)(n-1)/num_whole;

    z=0;
    n=num_whole;
    while(z< 0.025){
        z += choose(num_whole,num_male) * pow((double)n/num_whole, num_male) * pow((double)(num_whole-n)/num_whole, num_whole-num_male);
        printf("%lf\n",z);
        n --;
    }
    *upper_bound = (double)(n+1)/num_whole;
}

int choose(int n, int r)
{
    int i,bunbo,bunshi;

    bunbo=bunshi=1;
    for(i=n;i>r;i--) bunbo *= i;
    for(i=r;i>0;i--) bunshi *= i;
    return bunbo/bunshi;
}