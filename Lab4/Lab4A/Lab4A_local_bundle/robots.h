#ifndef ROBOTS_H
#define ROBOTS_H

#define MAXN  50
#define MAXM 100
#define MAXS 10000
#define EMPTY (-1)

typedef enum { DIR_N = 0, DIR_E = 1, DIR_S = 2, DIR_W = 3 } Direction;

typedef struct {
    char name[16];
    int  x, y;
    Direction dir;
} Robot;

Direction dir_from_char(char c);
char      char_from_dir(Direction d);
void      turn_left(Robot *r);
void      turn_right(Robot *r);
void      forward_delta(Direction d, int *dx, int *dy);
int       inside(int N, int x, int y);
int       find_robot(Robot *rs, int m, const char *name);
void      step_forward(int N, int occ[][MAXN], Robot R[], int idx);

#endif
