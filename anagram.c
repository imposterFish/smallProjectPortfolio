#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> //qsort
#include <time.h>
#include <ctype.h>

/* This program takes two strings as input, 
 * then runs them through two different algorithms.
 * Both algorithms determine if the two strings are anagrams of eachother,
 * then return true or false based on that.
 * Then the program will determine if the two functions returned the same answer.
 * 
 * I used gcc to to compile this program. I believe this defaults to gnu11
 * 
 * This was origionally from a "code review" interview. 
 * I later added comments about the program based off of what the interviewer asked me or any changes we made.
 *
 * Even later, I found an issue when using the two strings "abcdef" and "fedcba". I think that my isAnagram method has an issue.
 */

/* This function is my first implementation of an anagram checker.
 * This is not your typical anagram checker that uses sorting.
 */
bool isAnagram(char *spr1, char *spr2) { 
    if(strlen(spr1)!=strlen(spr2)) { // By deffinition if the two words are different lengths, they are not anagrams.
        return false;
    }
    
    int x,y; // Used in the nested for loops.
    int len=strlen(spr1); // This would be more useful if I decided to edit spr1 in the nested for loops.
    char temp[20];
    char temp2[20];
    strcpy(temp,spr1);

    /* Reasons why I did the following nested for loops:
     * I did not want to change the two inputted strings, so temp holds spr1. We will edit temp.
     *
     * I did not want to deal with multiple substrings, then putting them back together, so that's why
     * in the if statement, I'm only comparing the 0th element. I only have to deal with one side of the string.
     *
     */
    for(y=0; y<len; y++) { // This loop iterates through the length of spr1
        for (x=0; x<len; x++) { // This loop iterates through the length of spr2
            if(temp[0] == spr2[x]) { // We are just comparing the first element of temp to (each element of) spr2. 
                strcpy(temp2, temp); 
                strcpy(temp, *(&temp2)+1); // temp now points one value over. The first element is dropped.
                break; // We have a new first element. We start over comparing temp[0] to each element of spr2.
            }
        }
    }
    if (strlen(temp)>0) {
        return false; // If not all the elements matched, temp will not be empty.
    } else {
        return true; // If the strings are anagrams, temp should be 0.
    }
    
}

/* Comparison function for qsort.
 * It takes the pointers to two values, 
 * then we return a value that is used to decide sorting.
 */
int cmpfun(const void * a, const void * b) {
    // I used the line below to try and understand exactly what is going on.
    // printf("%i\n", *(char*)a - *(char*)b); 
    return ( *(char*)a - *(char*)b );
}

/* This is my second implementation of the anagram checker.
 * It sorts the strings before comparison.
 */
bool isAnaSort(char *spr1, char *spr2) {
    if(strlen(spr1)!=strlen(spr2)) { // By deffinition if the two words are different lengths, they are not anagrams.
        return false;
    }

    // Sorts the string in alphabetical order. cmpfun is the comparison function.
    qsort(spr1, (size_t) strlen(spr1), (size_t) sizeof('a'), cmpfun);
    qsort(spr2, (size_t) strlen(spr2), (size_t) sizeof('a'), cmpfun);

    int x; // I once had an issue with declaring a variable in a for loop in C.
    // This for loop (and if statement) compares each sorted string value. 
    // If they are anagrams, the strings should be the same after being sorted.
    for (x=0; x<strlen(spr2); x++) { // I could have used strcmp instead of this for loop.
        if (spr1[x] != spr2[x]) {
            return false; // If the strings are different, they are not anagrams.
        }
    }
    return true; // If the strings are the same, they are anagrams.
}

/* This method fixes the case of the string.
 * By deffinition, anagrams are not case sensitive.
 */
void fixCase(char *str) { 
    // I had the function return a "const char*", then attempted to use strcpy in the main function to then set the strings.
    // I completely overlooked the fact that the string is changed in the function and all of that is unnessesary.
    int x = 0;
    for (x=0; x<strlen(str); x++) {
        str[x] = tolower(str[x]);
    }
}

int main() {
    char str1[20]="";
    char str2[20]="";

    // Takes user input of 2 strings
    scanf("%s", str1);
    scanf("%s", str2);

    // Fixes the case of the strings
    fixCase(str1);
    fixCase(str2);

    if (isAnaSort(str1, str2) == isAnagram(str1, str2)) { // compares user's input and results from both anagram functions
        printf("Both methods work\n");
    } else {
        printf("There was an error\n");
    }

    return 0;
}