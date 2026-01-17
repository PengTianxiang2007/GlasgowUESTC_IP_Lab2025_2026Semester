#include <stdio.h>

long long XOR(long long a, long long b){
    return (a | b) & ~(a & b);  //or ~(a & b) & (a | b);  An XOR gate is obtained by superimposing a NAND gate and an OR gate.
}

int main(){
    long long n, sum;
    scanf("%lld",&n);
    sum = n;

    while(n>0){     //loop until n =1 and break the loop when n =0
        n = n>> 1; 
        sum = XOR( n , sum);   //let sum = n at the beginning,so in the first loop we can calculate XOR(n, n>>1)
    }

     printf("%lld",sum);
    return 0;
}

/*

Why n = n>> 1 means [n/2]?

The first step:if n is an odd number,the last bit must be 1 which will be dropped so the result to the even number n-1

The second step:we can see the even number as the sum of 2 to the power of n,when we move it to the right by 1 bie,
we can see that every component is divided by 2,because 2 to the power of (n-1) is equal to (2 to the power of n)/2

So the result is equal to n/2

*/
