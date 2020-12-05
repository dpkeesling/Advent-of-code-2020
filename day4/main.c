#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#undef DEBUG
//#define DEBUG 1

int find_valid_passports(char passports[299][200]);

int main() {
    FILE *fptr;
    fptr = fopen("./input.txt","r");
    char input[1170][200];
    char passports[299][200];
    int newline_index_tracker = 0;
    int passport_counter = 0;
    for (int i = 0; i < 1170; i++) {
        fgets(input[i], 200, fptr);
        //printf("%s", input[i]);
        if(input[i][0] == '\n' || i == 1169) {
            for(int j = newline_index_tracker; j < i; j++) {
                strcat(passports[passport_counter], input[j]);
            }
            #ifdef DEBUG
            printf("Passport %d is %s\n", passport_counter, passports[passport_counter]);
            #endif
            newline_index_tracker = i + 1;
            passport_counter++;
        }
    }
    printf("The total number of valid passports is %d\n", find_valid_passports(passports));
    return 0;
}

int find_valid_passports(char passports[299][200]) {
    const char *word_list[] = {"byr:","iyr:","eyr:","hgt:","hcl:","ecl:","pid:","cid:"};
    int valid_passports = 0;
    for(int i = 0; i < 299; i++) {
        bool valid = true;
        for(int j = 0; j <= 6; j++) {
            if(strstr(passports[i], word_list[j]) == NULL) {
                valid = false;
                break;
            }
        }
        if(valid) {
            valid_passports++;
        }
    }
    return valid_passports;
}

