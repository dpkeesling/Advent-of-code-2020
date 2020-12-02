#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#undef DEBUG
// #define DEBUG 1

void parse_policy(int *lower_bound, int *upper_bound, char *letter, char *password, char *string);
int getSubString(char *source, char *target,int from, int to);
bool check_policy(int lower_bound, int upper_bound, char letter, char *password);

int main(){
    FILE *fptr;
    fptr = fopen("./input.txt","r");
    char strings_array[1000][50];
    int compliant_passwords = 0;
    for (int i = 0; i < 1000; i++){
        int lower_bound = 0;
        int upper_bound = 0;
        char letter = 'a';
        char password[50];
        fgets(strings_array[i], sizeof(strings_array[i]), fptr);
        #ifdef DEBUG
        printf(strings_array[i]);
        #endif
        parse_policy(&lower_bound, &upper_bound, &letter, password, strings_array[i]);
        #ifdef DEBUG
        printf("Lower bound is %d, upper bound is %d, the letter is %c, and the password is %s\n", lower_bound, upper_bound, letter, password);
        #endif
        if(check_policy(lower_bound, upper_bound, letter, password)) {
            compliant_passwords++;
            #ifdef DEBUG
            printf("Match!\n");
            #endif
        }
    }
    printf("The total number of matching passwords is %d\n", compliant_passwords);
    return 0;
}

void parse_policy(int *lower_bound, int *upper_bound, char *letter, char *password, char *string) {
    for(int i = 0; i < strlen(string); i++) {
        bool first_space_found = false;
        int dash_index;
        #ifdef DEBUG
        printf("The character being looked at is %c\n", string[i]);
        #endif
        if (string[i] == '-') {
            char temp_substring[i];
            getSubString(string, temp_substring, 0, i);
            #ifdef DEBUG
            printf("The lower bound as a string is %s\n", temp_substring);
            #endif
            *lower_bound = atoi(temp_substring);
            dash_index = i;
        }
        else if (string[i] == ' ' && !first_space_found) {
            first_space_found = true;
            char temp_substring[i - dash_index];
            getSubString(string, temp_substring, dash_index + 1, i);
            #ifdef DEBUG
            printf("The upper bound as a string is %s\n", temp_substring);
            #endif
            *upper_bound = atoi(temp_substring);
        }
        else if (string[i] == ':') {
            *letter = string[i - 1];
            getSubString(string, password, i + 2, strlen(string));
            #ifdef DEBUG
            printf("The password as a string is %s and the letter is %s\n", password, letter);
            #endif
        }
    }

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

bool check_policy(int lower_bound, int upper_bound, char letter, char *password) {
    #ifdef DEBUG
    printf("The lower bound char is %c, the upper bound char is %c, the letter it should match is %c, and the full password is %s\n",
         password[lower_bound - 1], password[upper_bound - 1], letter, password);
    #endif
    return ((password[lower_bound - 1] == letter) || (password[upper_bound - 1] == letter)) && (password[lower_bound - 1] != password[upper_bound - 1]);
}
