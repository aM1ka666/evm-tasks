#include<stdio.h>

int task(FILE *in, long long *res);

int main(void){
    FILE *in;
    int err;
    long long res;

    in=fopen("1.txt", "r");
    err=task(in, &res);

    if(err==0){
        printf("Not file\n");
        return -1;
    }
    fclose(in);

    if(err==-1)
        printf("Bad file\n");
    if(err==-2)
        printf("Empty file\n");
    if(err==1){
        printf("result=%lld\n", res);
    }
    return 0;
}

int task(FILE *in, long long *res){
    long long cur, sum = 0, count = 0, total = 0;
    int err;

    *res=0;
    if(in==NULL)
        err=0;
    else{
        while(fscanf(in, "%lld", &cur)==1){
            if(cur == sum){
                count++;
            }
            sum += cur;
            total++;
        }
        if(!feof(in))
            err=-1;
        else{
            if (total==0)
                err=-2;
            else{
                *res = count;
                err=1;
            }
        }
    }
    return err;
}
