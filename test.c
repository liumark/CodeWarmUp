 #include <stdio.h>

#define PI 3.14

int findNumR(float r, float t) {
    int retVal = 1;
    float r1;
    float sum;

    while (sum <= t) {
        r1 = r + (retVal -1)*2;
        sum += (2*r1 + 1)*PI;
        retVal++;
    }
    return (retVal -1);
}

int main() {
    printf("%d\n", findNumR(1.0, 9));
    printf("%d\n", findNumR(1.0, 10));
    printf("%d\n", findNumR(3.0, 40));
    printf("%d\n", findNumR(1.0, 1E18));
}
