#include <stdio.h>
#include <string.h>

typedef struct {
    char name[1000];
    int score;
    int hour;
    int minute;
    int time;
}Record;

int main(){
    int n;
    scanf("%d",&n);

    Record records[1000];  //define an array of struct

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d:%d", records[i].name, &records[i].score, &records[i].hour, &records[i].minute);
        records[i].time = records[i].hour*60 + records[i].minute;
    }                      //input the data and calculate the differece in minutes

    for (int i = 0 ; i < n - 1 ; i++){  //n-1 is enough because the last one will be in the right position automatically
        Record temp;
        for (int j = 0 ; j < n - 1 - i ; j++){ //n-1-i beacuse some large score have already been in the right position
            if (records[j].score < records[j+1].score){  
                temp = records[j];  //every out loop will define the position of the relatively highest score
                records[j] = records[j+1];
                records [j+1] = temp;
            }
        }
    }

    for (int i = 0 ; i < n - 1 ; i++ ){
        Record temp;
        for (int j = 0 ; j < n - 1 - i ; j++){  //bubble the sort based on time if score is the same
            if (records[j].score == records[j+1].score && records[j].time > records[j+1].time){
                temp = records[j];
                records[j] = records[j+1];
                records [j+1] = temp;
            }       
        }
    }

    for (int i = 0 ; i < n - 1 ; i++){
        Record temp;
        for (int j = 0 ; j < n - 1 - i ; j++){
            if (records[j].score == records[j+1].score && records[j].time == records[j+1].time && 
            strcmp(records[j].name , records[j+1].name)>0){ //the return value of strcmp is an integer,
                        //if the first string is greater than the second,return a positive integer,
                temp = records[j];          //bubble the sort based on name if score and time are the same
                records[j] = records[j+1];
                records [j+1] = temp;
            }
        }
    }
 
    for (int i = 0 ; i < n ; i++ ){
        printf("%s\n",records[i].name);  //output the names in order
    }

    
    return 0;
}