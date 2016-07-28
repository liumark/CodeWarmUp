#include <stdio.h>

//In C, there is no power operator but only pow() funciton
//which input/output the double
int power10(int n) {
    if (n == 1) return 1;
    else return 10*power10(n-1);
}

int revNum(int dig, int num, int n) {
//    printf("%d %d %d\n", dig, num, n);
    if (n == 1) return dig;
    else {
        return dig*power10(n) + revNum(num%10, num/10, n-1);
    }
}

int main() {
    int a1=12345678;
    int dig_cnt = 1;
    int tmp = a1;
    while (tmp > 0) {
        tmp = tmp/10;
        dig_cnt++;
    }
    printf("input=%d reversed=%d\n", a1, revNum(0, a1, dig_cnt));
    return 0;
}
