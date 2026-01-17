#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gcd(int a,int b){
    if (b==0) return a;
    return gcd(b,a%b);
}

int main(){
    srand(time(NULL));
    int n,a0;
    scanf("%d %d",&n,&a0);
    int maxgcd=0;
    for(int cnt=1;cnt<=30;cnt++){
        int i = rand() % n;
        printf("? %d\n",i);
        fflush(stdout);
        int ai;
        scanf("%d",&ai);
        int bi;
        if (ai>a0){
            bi = ai - a0;
        }
        else{
            bi = a0 - ai;
        }
        maxgcd = gcd(maxgcd,bi);
    }
    printf("! %d",maxgcd);
    return 0;
}