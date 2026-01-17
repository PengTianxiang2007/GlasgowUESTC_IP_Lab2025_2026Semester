#include <stdio.h>

float series(float R1,float R2);
float parallel(float R1,float R2);
float Ohm_law(int U,float R); 
int main(void){
    int U = 12;
    float I;
    float R1, R2, R3, R4, R5, R6, R7, R8;
    scanf("%f %f %f %f %f %f %f %f", &R1, &R2, &R3, &R4, &R5, &R6, &R7, &R8);//Input different resistance values
    float R_l=series(R1,R2);//Calculate the total resistance of the two resistors in the left branch,name it R_l
    float R_c=parallel(R3,R4);//Calculate the total resistance of the two parallel branches in the middle and name it R_c
    float R_r=R5+parallel(R6,R7)+R8;
    /*Calculate the total resistance of the right branch,
     connect R6 and R7 in parallel, and then connect R5 and R8 in series*/
    float R_m=parallel(R_l,parallel(R_c,R_r));
    // parallel R_l and R_c, and then parallel R_r
    I = Ohm_law(U, R_m) * 1000.0;//Calculate the current according to Ohm's Law and convert it to mA
    printf("%.2f\n", I);//Print the current value and keep it to two decimal places
    return 0;
}

float series(float R1,float R2){
    double R;
    R=R1+R2*1.0;
    return R;
    //A function for calculating the total resistance in series
}
    float parallel(float R1,float R2){
        double R;
        R=(R1*R2)*1.0/(R1+R2);
        return R;
        //A function for calculating the total resistance in parallel
}
    float Ohm_law(int U,float R){
        double I;
        I=U/R;
        return I;
        //A function for calculating current using Ohm's law
}