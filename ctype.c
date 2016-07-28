#include <stdio.h>

typedef union {
    float value;
    struct {
        unsigned mantisa : 23;
        unsigned exponent : 8;
        unsigned sign : 1;
    } parts;
} float_cast;

void print_float(float value) {
   float_cast worktype;
    worktype.value = value;
    printf("value = %f\n", value);
    printf("mantisa: %x\nexponent: %x\nsign: %x\n", worktype.parts.mantisa, worktype.parts.exponent, worktype.parts.sign); 
}

int main() {
    print_float(0.15625);
    print_float(-0.15625);
    return 0;
}
