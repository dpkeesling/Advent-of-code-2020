#include <stdio.h>
#include <stdbool.h>

int main(){
    FILE *fptr;
    fptr = fopen("./input.txt","r");
    int numberArray[200];
    int i;
    for (i = 0; i < 200; i++){
        fscanf(fptr, "%d", &numberArray[i]);
    }

    bool valueFound = false;
    for(i = 0; i < 200 && valueFound == false; i++){
        int j;
        for(j = 0; j < 200 && valueFound == false; j++){
            if(numberArray[j] != numberArray[i]) {
                if(numberArray[j] + numberArray[i] == 2020){
                    printf("The sum that is 2020's product is %d\n", numberArray[j] * numberArray[i]);
                    printf("Their sum is %d\n",  numberArray[j] + numberArray[i]);
                    valueFound = true;
                }
            }
        }
    }
    return 0;
}
