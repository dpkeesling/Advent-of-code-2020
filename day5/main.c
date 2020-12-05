#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#undef DEBUG
#define DEBUG 1

int calculate_seat_id(char *bin_space_part);

int main(){
    FILE *fptr;
    fptr = fopen("./input.txt","r");
    char input[781][10];
    int seat_id_max = 0;
    for (int i = 0; i < 781; i++){
        int seat_id = 0;
        fgets(input[i], 12, fptr);
        #ifdef DEBUG
        printf("%s\n", input[i]);
        #endif
        seat_id = calculate_seat_id(input[i]);
        if(seat_id > seat_id_max) {
            seat_id_max = seat_id;
        }
    }
    printf("The highest seat ID is %d\n", seat_id_max);
    return 0;
}

int calculate_seat_id(char *bin_space_part) {
    int rows_max = 127;
    int rows_min = 0;
    int total_rows = 128;
    int final_row = 0;
    int columns_max = 7;
    int columns_min = 0;
    int total_columns = 8;
    int final_column = 0;
    for(int i = 0; i < 7; i++) {
        int remainder = total_rows % 2;
        if(bin_space_part[i] == 'F') {
            total_rows /= 2;
            rows_max -= (total_rows + remainder);
        }
        else {
            total_rows /= 2;
            rows_min += (total_rows - remainder);
        }
        #ifdef DEBUG
        printf("The row min is %d, the row max is %d\n", rows_min, rows_max);
        #endif
    }
    final_row = rows_min;
    for(int i = 7; i < 10; i++) {
        int remainder = total_columns % 2;
        if(bin_space_part[i] == 'L') {
            total_columns /= 2;
            columns_max -= (total_columns + remainder);
        }
        else {
            total_columns /= 2;
            columns_min += (total_columns - remainder);
        }
        #ifdef DEBUG
        printf("The column min is %d, the column max is %d\n", columns_min, columns_max);
        #endif
    }
    final_column = columns_min;
    return ((final_row * 8) + final_column);
}
