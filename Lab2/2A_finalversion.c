#include <stdio.h>
#include <stdlib.h>  //Include standard library header for rand, srand, time
#include <time.h>   //Include time header for seeding random number generator

#define MAX_QUERIES 30

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}  //Function to compute GCD of two numbers using Euclidean algorithm

int main() {
    srand(time(NULL));  
    /*Seed the random number generator with the current time 
    time(NULL) returns the current time in seconds since epoch
    srand() initializes the random number generator 
   If placed inside the loop, the loop could execute multiple times within the same second,
   it would reset with the same seed every time, yielding the same random number */

    int n;
    int a0;
    scanf("%d %d", &n, &a0);

    int resultGcd = 0;

    for (int i = 0; i < MAX_QUERIES; i++) {
        int queryIndex = rand() % n; 
         /*Generate a random index between 0 and n-1
        Each number in the sequence is deterministically calculated from the previous one*/

        printf("? %d\n", queryIndex);
        fflush(stdout); //Ensure the output is sent immediately,or else the judge may not receive it in time

        int queriedValue;
        scanf("%d", &queriedValue);

        int difference;   //Calculate the absolute difference between queried value and a0
        if (queriedValue > a0) {
            difference = queriedValue - a0;
        } else {
            difference = a0 - queriedValue;
        }      
        resultGcd = gcd(resultGcd, difference);  //Update the GCD with the new difference
    }

    printf("! %d\n", resultGcd);
    fflush(stdout);
    
    return 0;
}
