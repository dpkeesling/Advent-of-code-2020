#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#undef DEBUG
#define DEBUG 1
// NOTE: This doesn't work yet!!!

int find_valid_passports(char passports[299][200]);
int getSubString(char *source, char *target,int from, int to);

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
    const char *word_list[] = {"byr:","iyr:","eyr:","hgt:","hcl:","ecl:","pid:"};
    int valid_passports = 0;
    for(int i = 0; i <= 298; i++) {
        bool valid = true;
        for(int j = 0; j <= 6; j++) {
            char *word_buffer = strstr(passports[i], word_list[j]);
            #ifdef DEBUG
            printf("The word_buffer is %s\n", word_buffer);
            #endif
            if(word_buffer != NULL) {
                char *word_parsed = word_list[j];
                int value_starting_index = (word_buffer - passports[i]) + 4; // +4 is to get to the end of the keyword
                #ifdef DEBUG
                printf("Value starting index is %d\n", value_starting_index);
                #endif
                if(j == 0) {
                    char value[4];
                    int integer_value = 0;
                    getSubString(passports[i], value, value_starting_index, value_starting_index + 4);
                    integer_value = atoi(value);
                    if(integer_value < 1920 || integer_value > 2002) {
                        valid = false;
                    }
                }
                else if(j == 1) {
                    char value[4];
                    int integer_value = 0;
                    getSubString(passports[i], value, value_starting_index, value_starting_index + 4);
                    integer_value = atoi(value);
                    if(integer_value < 2010 || integer_value > 2020) {
                        valid = false;
                    }
                }
                else if(j == 2) {
                    char value[4];
                    int integer_value = 0;
                    getSubString(passports[i], value, value_starting_index, value_starting_index + 4);
                    integer_value = atoi(value);
                    if(integer_value < 2020 || integer_value > 2030) {
                        valid = false;
                    }
                }
                else if(j == 3) {
                    char *height_unit[] = {"in", "cm"};
                    char *inch_pointer = strstr(passports[i], height_unit[0]);
                    char *cm_pointer = strstr(passports[i], height_unit[1]);
                    if(inch_pointer != NULL) {
                        int unit_index = passports[i] - inch_pointer;
                        char number_string[4];
                        getSubString(passports[i], number_string, value_starting_index, unit_index);
                        int height_value = atoi(number_string);
                        if(height_value < 59 || height_value > 76) {
                            valid = false;
                        }
                    }
                    else if(cm_pointer != NULL) {
                        int unit_index = passports[i] - cm_pointer;
                        char number_string[4];
                        getSubString(passports[i], number_string, value_starting_index, unit_index);
                        int height_value = atoi(number_string);
                        if(height_value < 150 || height_value > 193) {
                            valid = false;
                        }
                    }
                    else {
                        valid = false;
                    }
                }
                else if(j == 4) {
                    char hair_color_value[7];
                    getSubString(passports[i], hair_color_value, value_starting_index, value_starting_index + 7);
                    if(hair_color_value[0] == '#') {
                        for(int k = 1; k <= 6; k++) {
                            if(!((hair_color_value[k] >= 'a' && hair_color_value[k] <= 'f') || (hair_color_value[k] >= '0' && hair_color_value[k] <= '9'))) {
                                valid = false;
                                break;
                            }
                        }
                    }
                    else {
                        valid = false;
                    }
                }
                else if(j == 5) {
                    char eye_color_value[3] = {0};
                    getSubString(passports[i], eye_color_value, value_starting_index, value_starting_index + 2);
                    #ifdef DEBUG
                    printf("The eye color value is %s\n", eye_color_value);
                    #endif
                    char *eye_color_wordlist[] = {"amb","blu","brn","gry","grn","hzl","oth"};
                    bool eye_color_value_valid = false;
                    for(int k = 0; k <= 6; k++) {
                        #ifdef DEBUG
                        printf("The strcmp result is %d\n", strcmp(eye_color_value, eye_color_wordlist[k]));
                        printf("eye color that is being checked against is %s\n", eye_color_wordlist[k]);
                        #endif
                        if(strcmp(eye_color_value, eye_color_wordlist[k]) == 0) {
                            eye_color_value_valid = true;
                            break;
                        }
                    }
                    valid = eye_color_value_valid;
                }
                else if(j == 6) {
                    char character_to_check = passports[i][value_starting_index];
                    int num_counter = 0;
                    while(character_to_check != ' ') {
                        num_counter++;
                        character_to_check = passports[i][value_starting_index + num_counter];
                    }
                    valid = (num_counter <= 9);
                }
            }
            else {
                valid = false;
            }
        }
        if(valid) {
            valid_passports++;
        }
    }
    return valid_passports;
}

// NOTE: I did not create this function. Here is the source: https://www.includehelp.com/c-programs/extract-a-portion-of-string-substring-extracting.aspx
int getSubString(char *source, char *target,int from, int to) {
	int length=0;
	int i=0,j=0;
	
	//get length
	while(source[i++]!='\0')
		length++;
	
	if(from<0 || from>length){
		printf("Invalid \'from\' index\n");
		return 1;
	}
	if(to>length){
		printf("Invalid \'to\' index\n");
		return 1;
	}	
	
	for(i=from,j=0;i<=to;i++,j++){
		target[j]=source[i];
	}
	
	//assign NULL at the end of string
	target[j]='\0'; 
	
	return 0;	
}

