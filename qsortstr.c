#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define ALLOCSIZE 10000

char* lineptr[MAXLINES];

static char allocbuf[ALLOCSIZE];
static char* allocp = allocbuf;

char* alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp -n;
    } else 
        return 0;
}

int getline1(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim -1 && ((c = getchar()) != EOF) && c != '\n'; i++)
        s[i] = c;

    if (i == 0) return -1;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

int readlines(char* lineptr[], int nlines);
void writelines(char* lineptr[], int nlines);
void qsort(char* lineptr[], int left, int right);

int main() {
    int nlines;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        //printf("read line %d", nlines);
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Error: %d input is too big to sort\n", nlines);
        return 1;
    }
}

#define MAXLEN 1000

int readlines(char* lineptr[], int maxlines) {
    char *p, line[MAXLEN];
    int len, nlines;

    nlines = 0;
    while ((len = getline1(line, MAXLEN)) >= 0) {
        //printf("len=%d", len);
        if (nlines > maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            //printf("Got line\n");
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

void writelines(char* lineptr[], int nlines) {
    int i;

    for (i = 0; i < nlines; i ++)
        printf("%s\n", lineptr[i]);
}

void swap(char**, int, int);
void qsort(char* v[], int left, int right) {
    int i, last;

    if (left >= right) return;

    swap(v, left, (left + right)/2);
    last = left;
    for (i = left + 1; i < right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);
    qsort(v, left, last -1);
    qsort(v, last + 1, right);
}

void swap(char* v[], int i, int j) {
    char *tmp;
    tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}
