#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NO_OF_CHARS 256

/********************* Find Longest SubString *********************
 * Length of the longest substring without repeating characters
 * URL: http://www.geeksforgeeks.org/length-of-the-longest-substring-without-repeating-characters/
*******************************************************************/
int longestUniqueSubsttr(char *str)
{
    int n = strlen(str);
    int cur_len = 1;  // lenght of current substring
    int max_len = 1;  // result
    int prev_index;  //  previous index
    int i;
    int *visited = (int *)malloc(sizeof(int)*NO_OF_CHARS);
 
    /* Initialize the visited array as -1, -1 is used to
       indicate that character has not been visited yet. */
    for (i = 0; i < NO_OF_CHARS;  i++)
        visited[i] = -1;
 
    /* Mark first character as visited by storing the index
       of first   character in visited array. */
    visited[str[0]] = 0;
 
    /* Start from the second character. First character is
       already processed (cur_len and max_len are initialized
       as 1, and visited[str[0]] is set */
    for (i = 1; i < n; i++)
    {
        prev_index =  visited[str[i]];
 
        /* If the currentt character is not present in the
           already processed substring or it is not part of
           the current NRCS, then do cur_len++ */
        if (prev_index == -1 || i - cur_len > prev_index)
            cur_len++;
 
        /* If the current character is present in currently
           considered NRCS, then update NRCS to start from
           the next character of previous instance. */
        else
        {
            /* Also, when we are changing the NRCS, we
               should also check whether length of the
               previous NRCS was greater than max_len or
               not.*/
            if (cur_len > max_len)
                max_len = cur_len;
 
            cur_len = i - prev_index;
        }
 
        // update the index of current character
        visited[str[i]] = i;
    }
 
    // Compare the length of last NRCS with max_len and
    // update max_len if needed
    if (cur_len > max_len)
        max_len = cur_len;
 
    free(visited); // free memory allocated for visited
    return max_len;
}
 
/* A utility function to get the minimum of two integers */
int min(int a, int b)
{
    return (a>b)?b:a;
}
 
/* Driver program to test above function */
void findLongestSubstring()
{
    char str[] = "ABDEFGABEF";
    printf("The input string is %s \n", str);
    int len =  longestUniqueSubsttr(str);
    printf("The length of the longest non-repeating "
           "character substring is %d\n", len);
}

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
    findLongestSubstring();
    return 0;
}
