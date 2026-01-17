#include <stdio.h>
int main(void){
    int cal_cre,pro_cre,ano_cre,cal_gra,pro_gra,ano_gra;      
    scanf("%d %d %d",&cal_cre,&pro_cre,&ano_cre);     //input the credits of three courses
    scanf("%d %d %d",&cal_gra,&pro_gra,&ano_gra);      //input the grades of three coreses
    printf("%.0lf",(cal_cre*cal_gra+pro_cre*pro_gra+ano_cre*ano_gra)*1.0/(cal_cre+pro_cre+ano_cre));
    //calculate the GPA and Convert to float and round to the nearest integer
    return 0;
} 