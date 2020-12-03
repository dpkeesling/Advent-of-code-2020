#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef DEBUG
//#define DEBUG 1

int get_num_of_trees(char tree__map[323][32]);

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
    printf("The number of trees you would encounter is %d\n", get_num_of_trees(tree_map));
    return 0;
}

int get_num_of_trees(char tree__map[323][32]) {
    int x_coord = 0;
    int y_coord = 0;
    int tree_count = 0;
    for(int i = 0; i < 323; i++) {
        x_coord = ((x_coord + 3) % 31);
        y_coord += 1;
        if(tree__map[y_coord][x_coord] == '#') {
            tree_count++;
        }
    }
    return tree_count;
}
