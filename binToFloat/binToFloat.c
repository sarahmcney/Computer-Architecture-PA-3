#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of float point number
    char buff;
    bool sign;
    unsigned int binary = 0;
    bool binary_bitstring[32];
    for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB first as that is what comes first in the file
        fscanf(fp, "%c", &buff);
        binary += buff == '1' ? (1 << i): 0;
        if(i == EXP_SZ+FRAC_SZ) {
            if(buff == '1') {
                sign = true; //true = negative
            } else {
                sign = false;
            }
        }
        if(buff == '1') {
                binary_bitstring[31 - i] = 1;
            } else {
                binary_bitstring[31 - i] = 0;
            }
    }
    //printf("%d\n", binary);


    // E
    bool exponent_field[8];
    int E = 0;
    for(int i = 0; i < 8; i++) {
        exponent_field[i] = binary_bitstring[i+1];
    }
    for(int i = 0; i < 8; i++) {
        //printf("%d ", exponent_field[i]);
        if(exponent_field[i] == 1) {
            E += pow(2, 7-i);
            //printf("i = %d\n", i);
        }
    }
    //printf("E = %d\n", E);
    E = E - 127;
    //printf("\nE = %d\n", E);

    /* ... */

    // M
    bool mantissa[23];
    double M = 0.0;
    for(int i = 0; i < 23; i++) {
        mantissa[i] = binary_bitstring[i+9];
    }
    for(int i = 0; i < 23; i++) {
        //printf("%d ", mantissa[i]);
    }

    /*for(int i = 0; i <= 22; i++) {
        if(mantissa[i] == 1) {
            printf("%d ", 23-i);
            M += 1/pow(2, 23-i);
        }
    }*/
    for(int i = 0; i < 23; i++) {
        M += mantissa[i]*(1/(pow(2, i+1)));
    }
    M = M + 1.0;
    //M = M + 1.0;
   // printf("\n%lf\n", M);
    /*char mantissa[24];
    for(int i = 0; i < 23; i++) {
        if(binary_bitstring[i+9] == 0){
            mantissa[i] = '0';
        } else {
            mantissa[i] = '1';
        }
    }
    for(int i = 0; i < 23; i++) {
        //printf("%c ", mantissa[i]);
    }
    mantissa[23] = '\0';
    double M = atoi(mantissa);
    //printf("\n%lf\n", M); 

    //char idk[7] = {'0', '1', '1', '0', '1', '0', '\0'};
    //double M_2 = atoi(idk);
    //printf("%lf\n", M_2);
    while(M > 1.0) {
        M = M / 10;
    }
    //printf("%lf\n", M);
    int padding = 0;
    for(int i = 0; i < 23; i++) {
        if(mantissa[i] == '1') {
            padding = i;
            break;
        }
    }
    M = M * pow(10, (-1*padding));
    M = M + 1.0;
    printf("%lf\n", M);*/


     

    // https://www.tutorialspoint.com/c_standard_library/c_function_ldexp.htm
    double number = ldexp ( M, E );
    number = sign ? -number : number;
    printf("%f\n", number);

    return EXIT_SUCCESS;

}
