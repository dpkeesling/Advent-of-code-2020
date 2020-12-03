#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef DEBUG
//#define DEBUG 1

unsigned long int get_product_of_trees(char tree_map[323][32]);
unsigned long int get_num_of_trees(char tree_map[323][32], int x_slope, int y_slope);

int main() {
    FILE *fptr;
    fptr = fopen("./input.txt","r");
    char tree_map[323][32];
    for (int i = 0; i < 323; i++) {
        fgets(tree_map[i], 33, fptr);
        #ifdef DEBUG
        printf("%s", tree_map[i]);
        #endif
    }
    printf("The product of the number of trees you would encounter on all the slopes is %lu\n", get_product_of_trees(tree_map));
    return 0;
}

unsigned long int get_product_of_trees(char tree_map[323][32]) {
    return (get_num_of_trees(tree_map, 1, 1) * get_num_of_trees(tree_map, 3, 1) * get_num_of_trees(tree_map, 5, 1) * get_num_of_trees(tree_map, 7, 1) * get_num_of_trees(tree_map, 1, 2));
}

unsigned long int get_num_of_trees(char tree_map[323][32], int x_slope, int y_slope) {
    int x_coord = 0;
    int y_coord = 0;
    int tree_count = 0;
    for(int i = 0; i < 323; i++) {
        x_coord = ((x_coord + x_slope) % 31);
        y_coord += y_slope;
        if((y_coord <= 323) && (tree_map[y_coord][x_coord] == '#')) {
            tree_count++;
        }
    }
    return tree_count;
}
