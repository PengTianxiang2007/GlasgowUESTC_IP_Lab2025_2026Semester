#include <stdio.h>
#include <string.h>
#include "robots.h"

/* --- Some constants and types are defined in robots.h (use in your TODOs and do NOT modify, and do NOT redefine them here) --- */

/* Direction tables for convenience (do NOT modify) */
static const int DX[4]       = { 0, 1, 0,-1 };  // step in x for N,E,S,W
static const int DY[4]       = { 1, 0,-1, 0 };  // step in y for N,E,S,W
static const Direction LEFT_OF[4]  = { DIR_W, DIR_N, DIR_E, DIR_S };
static const Direction RIGHT_OF[4] = { DIR_E, DIR_S, DIR_W, DIR_N };


/* -------- TODOs: implement the following helper functions -------- */

/* Convert a direction character (`N',`E',`S',`W') to a Direction value
   If c is not one of these, return DIR_N by default. */
Direction dir_from_char(char c){            //row52,translate the input language to enum,whinch can be understood by computer
    if (c == 'N'){
        return DIR_N;
    }
    else if (c == 'E'){
        return DIR_E;
    }
    else if (c == 'S'){
        return DIR_S;
    }
    else if (c == 'W'){
        return DIR_W;
    }
    else{
        return DIR_N;
    }
}
/* Convert a Direction value to the corresponding character (`N',`E',`S',`W'). */
char char_from_dir(Direction d){             //row81 translate the enum to output language, whinch can be understood by human
    if (d == DIR_N){
        return 'N';
    }
    else if (d == DIR_E){
        return 'E';
    }
    else if (d == DIR_S){
        return 'S';
    }
    else if (d == DIR_W){
        return 'W';
    }
    else{
        return 'N';
    }
}

/* Rotate the robot 90 degrees to the left (counterclockwise). */
void turn_left(Robot *r){             //row68, change the direction of robot when it turns left
    if (r->dir == DIR_N){        //r is a pointer point to the robot struct,which can change the value of the direction of the robot
        r->dir = DIR_W;          //if we do not use pointer,we only change the copy of the robot struct in the function stack
    }
    else if (r->dir == DIR_W){
        r->dir = DIR_S;
    }
    else if (r->dir == DIR_S){
        r->dir = DIR_E;
    }
    else if (r->dir == DIR_E){
        r->dir = DIR_N;
    }
}

/* Rotate the robot 90 degrees to the right (clockwise). */
void turn_right(Robot *r){             //row69, change the direction of robot when it turns right
    if (r->dir == DIR_N){
        r->dir = DIR_E;
    }
    else if (r->dir == DIR_E){
        r->dir = DIR_S;
    }
    else if (r->dir == DIR_S){
        r->dir = DIR_W;
    }
    else if (r->dir == DIR_W){
        r->dir = DIR_N;
    }
}

/* Compute the forward step for a given direction.
   After calling this, (*dx,*dy) should hold the change in (x,y)
   if a robot moves one cell forward while facing d. */
void forward_delta(Direction d, int *dx, int *dy){
    if (d == DIR_N){        //the function is uesd in the step_forward function to simplify the process of calculating the new position according to the direction
        *dx = 0;
        *dy = 1;
    }
    else if (d == DIR_E){
        *dx = 1;
        *dy = 0;
    }
    else if (d == DIR_S){
        *dx = 0;
        *dy = -1;
    }
    else if (d == DIR_W){
        *dx = -1;
        *dy = 0;
    }
}

/* Return 1 if (x,y) is inside the N x N grid (0 <= x < N, 0 <= y < N),
   otherwise return 0. */
int inside(int N, int x, int y){  //check whether the new position is inside the grid,used in step_forward function to decide whether the robot can move forward
    if (x >= 0 && x < N && y >= 0 && y < N){
        return 1;  //inside the grid,return 1 means the next step can be executed 
    }
    else{
        return 0;
    }
}

/* Find the index of the robot whose name matches `name` in rs[0..m-1].
   Return the index if found, or -1 if there is no such robot. */
int find_robot(Robot *rs, int m, const char *name){  //row65,search the robot so the next step can be executed on the right robot
    for (int i = 0; i < m; i++){      //rs is a pointer point of the struct Robot array,using for loop to check all the robots inside
        if (strcmp(rs[i].name, name) == 0){  //the function strcmp:compare two strings,if they are the same,return 0
            return i;                 //if found,return i as the idx
        }
    }
    return -1;
}

/* Move R[idx] according to the defined rule. 
   - occ[y][x] is either EMPTY or a robot's index.*/
void step_forward(int N, int occ[][MAXN], Robot R[], int idx){    //row70,move the robot if the condition is satisfied
    int dx, dy;                             
    forward_delta(R[idx].dir, &dx, &dy);    //using the function forward_delta to try to move the robot,the attempt will be tested later
    int new_x = R[idx].x + dx;
    int new_y = R[idx].y + dy;

    if(inside(N, new_x, new_y)==0){  //check whether the new position is inside the grid
        return;                     //if not inside,do not move
    }

    if (occ[new_y][new_x] != EMPTY){  //check whether the new position is occupied by another robot
        printf("COLLISION %s %s\n", R[idx].name, R[occ[new_y][new_x]].name);  //if occupied,print the collision message
        return;  //the first %s is the name of the robot,get by viewing R[idx].name,the name of the another robot is get by get the index,in the array R,which is stored in occ[new_y][new_x]
    //soruce:get the index of the robot by viewing the number stored in occ[new_y][new_x],then use the index to get the name of the robot in the array R 
    }

    occ[R[idx].y][R[idx].x] = EMPTY; // Mark old position as empty so this position can be used by other robots later
    R[idx].x = new_x;               //making the attempted move to be the real move,because we have passed the two tests
    R[idx].y = new_y;
    occ[new_y][new_x] = idx; // Mark new position with robot index,so we can know which robot is on a specific position directly
}
