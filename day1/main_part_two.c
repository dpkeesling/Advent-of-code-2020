#include <stdio.h>
#include <stdbool.h>

int main(){
    FILE *fptr;
    fptr = fopen("./input.txt","r");
    int numberArray[200];
    for (int i = 0; i < 200; i++){
        fscanf(fptr, "%d", &numberArray[i]);
    }
    bool valueFound = false;
    for(int i = 0; i < 200 && valueFound == false; i++){
        for(int j = 0; j < 200 && valueFound == false; j++){
            for(int k = 0; k < 200 && valueFound == false; k++) {
                if(numberArray[j] != numberArray[i] && numberArray[k] != numberArray[i] && numberArray[k] != numberArray[j]) {
                    if(numberArray[j] + numberArray[i] + numberArray[k] == 2020){
                        printf("The sum that is 2020's product is %d\n", numberArray[j] * numberArray[i] * numberArray[k]);
                        printf("Their sum is %d\n",  numberArray[j] + numberArray[i] + numberArray[k]);
                        valueFound = true;
                    }
                }
            }
        }
    }
    return 0;
}
