#include <stdio.h>

long long XOR(long long a, long long b){
    return (a | b) & ~(a & b);  //or ~(a & b) & (a | b);  An XOR gate is obtained by superimposing a NAND gate and an OR gate.
}


int main(){
    long long n , sum = 0;  /*the sum can only be 0 because in the first loop we have to assign sum = n 
    scanf("%lld",&n);                   so we can calculate XOR(n, n>>1)starting from the second loop    */

    while( n > 0 ){
        sum = XOR(sum , n);    //in the first loop,sum = n; so the next loop we will calculate XOR(n, n>>1)
        n = n >> 1;
    }

    printf("%lld",sum);
    return 0;
}