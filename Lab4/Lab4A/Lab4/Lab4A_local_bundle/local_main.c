/* A minimal README for this source code
    - What it is:
        The main function implementation for the robot simulator in Lab 4A of UESTC1005 Introductory Programming.
    - Directory structure (put everything below in one folder):
        robots.h      : Header file with type and function declarations (download from Moodle if you have not already).
        robots.c      : Your implementation of the helper functions.
        local_main.c  : This file, containing the main() function.
   - How to build (locally):
    gcc -std=c11 -Wall -Wextra -Werror -pedantic robots.c local_main.c -o sim
   - How to run:
    ./sim
    [paste input, then EOF: Ctrl+D on Linux/macOS; Ctrl+Z Enter on Windows; You can also manually type each line of input should you wish to do so]
*/

#include <stdio.h>
#include <string.h>
#include "robots.h"

/* Uncomment to print a tiny trace after each command (for self-debugging) */
// #define TRACE 1

#if TRACE
static void dump_state(int N, int m, const Robot R[]) {
    (void)N;
    for (int i = 0; i < m; ++i) {
        printf("[STATE] %s %d %d %c\n",
               R[i].name, R[i].x, R[i].y, char_from_dir(R[i].dir));
    }
}
#endif

int main(void) {
    int N, m, s;
    if (scanf("%d %d %d", &N, &m, &s) != 3) {
        return 0; /* silent exit on malformed input */
    }

    Robot R[MAXM];
    int occ[MAXN][MAXN];

    /* init occupancy grid to EMPTY */
    for (int y = 0; y < N; ++y)
        for (int x = 0; x < N; ++x)
            occ[y][x] = EMPTY;

    /* read robots: name x y D */
    for (int i = 0; i < m; ++i) {
        char dchar;
        if (scanf("%15s %d %d %c", R[i].name, &R[i].x, &R[i].y, &dchar) != 4) {
            return 0; /* malformed line → stop */
        }
        R[i].dir = dir_from_char(dchar);

        /* Assume inputs are valid & unique (as in official tests). */
        if (R[i].y >= 0 && R[i].y < N && R[i].x >= 0 && R[i].x < N) {
            occ[R[i].y][R[i].x] = i;
        }
    }

    /* process s commands: "<name> <C>" with C in {L,R,F} */
    for (int k = 0; k < s; ++k) {
        char name[16], cmd;
        if (scanf("%15s %c", name, &cmd) != 2) break;

        int idx = find_robot(R, m, name);      /* exact match */
        if (idx < 0) continue;                 /* ignore unknown names */

        if      (cmd == 'L') turn_left(&R[idx]);
        else if (cmd == 'R') turn_right(&R[idx]);
        else if (cmd == 'F') step_forward(N, occ, R, idx);
        /* silently ignore any other command */

        #if TRACE
        dump_state(N, m, R);
        #endif
    }

    /* final states (declaration order) */
    for (int i = 0; i < m; ++i) {
        printf("%s %d %d %c\n",
               R[i].name, R[i].x, R[i].y, char_from_dir(R[i].dir));
    }
    return 0;
}
