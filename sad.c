#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define FRAME_ROW 32
#define FRAME_COLUMN 32

#define WINDOW_ROW 8
#define WINDOW_COLUMN 4

// frame functions
int look_for_sad(int frame[FRAME_ROW][FRAME_COLUMN], int window[WINDOW_ROW][WINDOW_COLUMN], int rowIndex, int colIndex);
int traverse_frame(int frame[FRAME_ROW][FRAME_COLUMN], int window[WINDOW_ROW][WINDOW_COLUMN]);

int main(void) {

    // test frame/window
    int frame[32][32] = { { 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8},
                 {1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7 },
                 {1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7 },
                 {1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7 },
                 {1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7 },
                 {1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7 },
                 {1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7 },
                 {1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7 },
                 {1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7 },
                 {1, 1, 1, 1, 1, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8 },
                 {1, 1, 1, 1, 1, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8 },
                 {1, 1, 1, 1, 1, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8 },
                 {1, 1, 1, 1, 1, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8 }};
    int window[8][4] = { { 9, 9, 9, 9},
                  {9, 9, 9, 9 },
                  {9, 9, 9, 9},
                  {9, 9, 9, 9},
                  {9, 9, 9, 9},
                  {9, 9, 9, 9},
                  {9, 9, 9, 9},
                  {9, 9, 9, 9 }};



    traverse_frame(frame, window);

    return 0;
}

int traverse_frame(int frame[FRAME_ROW][FRAME_COLUMN], int window[WINDOW_ROW][WINDOW_COLUMN]) { // at any point in MIPS, do calculate_sad where
                      // there is a printf
    int row = 0;
    int col = 0;

    int count = 0;

    int min_sad = 9000;
    int min_sad_col = 0;
    int min_sad_row = 0;

    bool goingUp = true;

    if (look_for_sad(frame, window, row, col) <= min_sad) { // for (0,0)
        min_sad = look_for_sad(frame, window, row, col);
        min_sad_col = col;
        min_sad_row = row;
    }

    while (count < ((FRAME_COLUMN - 1))) {
        if (goingUp == false) {
            while (col > 0) { //zig
                row++;
                col--;
                if ((row <= (FRAME_ROW - WINDOW_ROW)) && (col >= 0)) {  //if_row_L_frame
                    if (look_for_sad(frame, window, row, col) <= min_sad) { //check min sad
                        min_sad = look_for_sad(frame, window, row, col);
                        min_sad_col = col;
                        min_sad_row = row;
                        printf("(%d,%d)", row, col);
                    }
                }
            }
            row++;
            if ((row <= (FRAME_ROW - WINDOW_ROW)) && (col >= 0)) {
                if (look_for_sad(frame, window, row, col) <= min_sad) {
                    min_sad = look_for_sad(frame, window, row, col);
                    min_sad_col = col;
                    min_sad_row = row;
                    printf("(%d,%d)", row, col);
                }
            }

            goingUp = true;
        }
        else { // goingUp == true
            while (row > 0) {
                col++;
                row--;
                if ((row <= (FRAME_ROW - WINDOW_ROW)) && (col < (FRAME_COLUMN - WINDOW_COLUMN))) {
                    if (look_for_sad(frame, window, row, col) <= min_sad) {
                        min_sad = look_for_sad(frame, window, row, col);
                        min_sad_col = col;
                        min_sad_row = row;
                        printf("(%d,%d)", row, col);
                    }
                }
            }
            col++;
            if ((row >= (FRAME_ROW - WINDOW_ROW)) && (col < (FRAME_COLUMN - WINDOW_COLUMN))) {
                if (look_for_sad(frame, window, row, col) <= min_sad) {
                    min_sad = look_for_sad(frame, window, row, col);
                    min_sad_col = col;
                    min_sad_row = row;
                    printf("(%d,%d)", row, col);
                }
            }

            goingUp = false;
        }

        count++;
    }

    while (count < (2 * (FRAME_ROW - 1))) {    //next
        if (goingUp == false) { // moving down the frame
            while (row < (FRAME_ROW - 1)) {
                row++;
                col--;

                if ((row <= (FRAME_ROW - WINDOW_ROW)) && (col <= (FRAME_COLUMN - WINDOW_COLUMN))) {
                    if (look_for_sad(frame, window, row, col) <= min_sad) {
                        min_sad = look_for_sad(frame, window, row, col);
                        min_sad_col = col;
                        min_sad_row = row;
                        printf("(%d,%d)", row, col);
                    }
                }
            }
            col++;
            if ((row <= (FRAME_ROW - WINDOW_ROW)) && (col <= (FRAME_COLUMN - WINDOW_COLUMN))) {
                if (look_for_sad(frame, window, row, col) <= min_sad) {
                    min_sad = look_for_sad(frame, window, row, col);
                    min_sad_col = col;
                    min_sad_row = row;
                    printf("(%d,%d)", row, col);
                }
            }

            goingUp = true;
        }
        else { // goingUp == true (moving up the frame)
            while (col < (FRAME_COLUMN - 1)) {
                col++;
                row--;
                if ((row <= (FRAME_ROW - WINDOW_ROW)) && (col <= (FRAME_COLUMN - WINDOW_COLUMN))) {
                    if (look_for_sad(frame, window, row, col) <= min_sad) {
                        min_sad = look_for_sad(frame, window, row, col);
                        min_sad_col = col;
                        min_sad_row = row;
                        printf("(%d,%d)", row, col);
                    }
                }
            }
            row++;
            if ((row <= (FRAME_ROW - WINDOW_ROW)) && (col <= (FRAME_COLUMN - WINDOW_COLUMN))) {
                if (look_for_sad(frame, window, row, col) <= min_sad) {
                    min_sad = look_for_sad(frame, window, row, col);
                    min_sad_col = col;
                    min_sad_row = row;
                    printf("(%d,%d)", row, col);
                }
            }
            goingUp = false;
        }
        count++;
    }
    return min_sad;
}

int look_for_sad(int frame[FRAME_ROW][FRAME_COLUMN], int window[WINDOW_ROW][WINDOW_COLUMN], int rowIndex, int colIndex) {

    int sadSum = 0;

    for (int i = rowIndex; i < (WINDOW_ROW + rowIndex); ++i) {
        for (int j = colIndex; j < (WINDOW_COLUMN + colIndex); ++j) {
            sadSum = sadSum + abs(frame[i][j] - window[i - rowIndex][j - colIndex]); // need offset
        }
    }
    return sadSum; // must check minimum after calling, as well as must check if out of bounds condition holds
}