#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECONDS_PER_YEAR (60UL * 60UL * 24UL * 365UL)
#define MIN(A,B) ((A <= B) ? (A) : (B))
#define BIT5 (0x1<<5)
#define CAT(a, b) a##b

static int d = 0xFF;

void swap(unsigned* x, unsigned* y) {
    *x = *x - *y;
    *y = *x + *y;
    *x = *y - *x;
}

void set_bit5() {
    d|=BIT5;
}

void clear_bit5() {
    d &= ~BIT5;
}

void foo(void) {
    unsigned int a = 6;
    int b = -20;
    (a+b > 6) ? puts(">6") : puts("<=6");
//    puts("\n");
}

void check_malloc() {
    char * ptr;
    if ((ptr=(char*)malloc(0))==NULL) {
        puts("Got a null pointer");
    } else {
        puts("Got a valid pointer");
    }
}

void check_endian() {
    union Test
    {
        unsigned int i;
        unsigned char c[2];
    };

    union Test a = {300};
    if ((a.c[0] == 1) && (a.c[1] == 44))
    {
        printf("Big Endian!\n");
    } else {
        printf("Little Endian!\n");
    }
}

const char* byte_to_binary(int x) {
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>=1) {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

int count_bit_set(unsigned char c) {
    int i = 0;

    while(c) {
        c = c & (c - 1);
        i++;
    }

    return i;
}

long ipaddr2int(const char* ipstr) {
    long retVal = 0;

    while(*ipstr) {
        retVal = retVal*10 + (*ipstr - '0');
        ipstr++;

        if (ipstr != 0 && *ipstr == '.') ipstr++;
    }
    return retVal;
}

int main() {
int a = 3;
int b = 5;
int ab = 35;
unsigned m = 7;
unsigned n = 17;
long lc = 0L;

    printf("seconds per year: %lu\n", SECONDS_PER_YEAR);
    printf("MIN(%d, %d) = %d\n", a, b, MIN(a, b));
    //MIN(a++, b) should not work since "a++" is copied to everywhere in the macro
    //printf("MIN(%d++, %d) = %d\n", a, b, MIN(a++, b));
    printf("a=%d, b=%d\n", a, b);
    printf("CAT(a, b): %d\n", CAT(a, b));
    clear_bit5();
    printf("clear_bit5() %X\n", d);
    set_bit5();
    printf("set_bit5() %X\n", d);
    foo();
    printf("bit mask %X\n", ~0);
    check_malloc();
    check_endian();
    printf("before swap: m=%d n=%d\n", m, n);
    swap(&m, &n);
    printf("after swap: m=%d n=%d\n", m, n);
    //print the binary of ~ operator
    printf("~0: binary %s, integer %d\n", byte_to_binary(~0), ~0);
    printf("~-1: binary %s, integer %d\n", byte_to_binary(~-1), ~-1);
    printf("-7: binary %s, integer %d\n", byte_to_binary(-7), -7);
    printf("c has value(%d), binary(%s), %d bit set\n", 'c', byte_to_binary('c'), count_bit_set('c'));
    //Print the max integer
    a=((unsigned)(~0))>>1;
    printf("MAX INT: %d\n", a);
    //replace sizeof()
    printf("sizeof(a): %d\n", (int)((char *)(&a+1) - (char *)&a));
    printf("sizeof(lc): %d\n", (int)((char *)(&lc+1) - (char *)&lc));
    printf("sizeof(int): %lu\n", sizeof(int));
    //convert ip address
    printf("[252.253.254.255] converted to %ld\n", ipaddr2int("252.253.254.255"));
}
