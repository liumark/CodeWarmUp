#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/************************ Reverse String **************************
 * Swap the value of the 2 variables
******************************************************************/
void swap(char* x, char* y) {
    if (*x != *y) {
        *x ^= *y;
        *y ^= *x;
        *x ^= *y;
    }
}

/************************ Reverse String **************************
 * Reverse the input string with the recursive calls by taking the
 * character from the tail and put to the head.
******************************************************************/
void revStr1(char* instr, char* outstr, int curP) {
    strncat(outstr,&instr[curP-1],1); //Each time, pick the last character in the string
                                      //Each time, only copy one character
    //printf("%s\n",outstr);
    if (curP > 1) {
        curP--;
        revStr1(instr, outstr, curP);
    } else if (curP == 1) outstr[strlen(instr)]='\0';
}

void reverseString1() {
    char a1[]="abcdefghijklmnopqrstuvwxyz0123456789";
    char* a2=(char*)malloc(sizeof(char)*strlen(a1));
    revStr1(a1,a2,strlen(a1));
    printf("input=%s length=%lu\nreversed=%s\n", a1, strlen(a1), a2);
    free(a2);
}
/******************************************************************/

/************************ Reverse String **************************
 * Reverse the input string with the recursive calls by swapping the
 * characters on the both ends.
******************************************************************/
void revStr2(char instr[], int begin, int end) {
    //printf("%s %d %d\n",instr, begin, end);
    if (begin >= end) return;
    else {
        swap(&instr[begin], &instr[end]);
        revStr2(instr, ++begin, --end);
    } 
}

void reverseString2() {
    char a1[]="abcdefghijklmnopqrstuvwxyz0123456789";
    printf("input=%s length=%lu\n",a1, strlen(a1));
    revStr2(a1,0,strlen(a1) - 1);//The end index must be -1
    printf("reversed=%s\n", a1);
}
/******************************************************************/

int main() {
    reverseString1();
    reverseString2();
    return 0;
}
