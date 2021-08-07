#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int main(int argc, char *argv[]) {

    // float value = *(float *) &binary; // you are not allowed to do this.
    // unsigned int binary = *(unsigned int*) &value; // you are not allowed to do this.

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    char buff[1];
    bool sign;
    bool multiplier_arr[32]; // suggested that you store bits as array of bools; minuend[0] is the LSB
    for (int i=0; i<32; i++) { // read MSB first as that is what comes first in the file
        /* ... */
        fscanf(fp, "%c", buff);
        if(i == 0) {
            if(buff[0] == '0') {
                sign = false;
            } else {
                sign = true;
            }
        }
        if(buff[0] == '0') {
            multiplier_arr[i] = false;
        } else {
            multiplier_arr[i] = true;
        }
    }
    

    // notice that you are reading two different lines; caution with reading
    /* ... */
    fscanf(fp, "%c", buff); //should catch newline char
    
    bool multiplicand_arr[32]; // suggested that you store bits as array of bools; subtrahend[0] is the LSB
    for (int i=0; i<32; i++) { // read MSB first as that is what comes first in the file
        /* ... */
        fscanf(fp, "%c", buff);
        if(buff[0] == '0') {
            multiplicand_arr[i] = false;
        } else {
            multiplicand_arr[i] = true;
        }
    }

    for(int i = 0; i < 32; i++) {
        //printf("%d", multiplier_arr[i]);
    }
    //printf("\n");
    for(int i = 0; i < 32; i++) {
        //printf("%d", multiplicand_arr[i]);
    }
    //printf("\n");


    //convert multiplier to fp
    //e
    bool exponent_field[8];
    int E = 0;
    for(int i = 0; i < 8; i++) {
        exponent_field[i] = multiplier_arr[i + 1];
    }
    for(int i = 0; i < 8; i++) {
        if(exponent_field[i] == 1) {
            E += pow(2, 7 - i);
        }
    }
    E = E - 127;
    //m
    bool mantissa[23];
    double M = 0.0;
    for(int i = 0; i < 23; i++) {
        mantissa[i] = multiplier_arr[i+9];
    }
    for(int i = 0; i < 23; i++) {
        M += mantissa[i]*(1/(pow(2, i+1)));
    }
    M = M + 1.0;

    double multiplier = ldexp(M, E);
    multiplier = sign ? -multiplier: multiplier;
    //printf("multiplier = %f\n", multiplier);

    //multiplicand
    if(multiplicand_arr[0] == 1) {
        sign = true;
    } else {
        sign = false;
    }
    E = 0;
    for(int i = 0; i < 8; i++) {
        exponent_field[i] = multiplicand_arr[i + 1];
    }
    for(int i = 0; i < 8; i++) {
        if(exponent_field[i] == 1) {
            E += pow(2, 7 - i);
        }
    }
    E = E - 127;
    M = 0.0;
    for(int i = 0; i < 23; i++) {
        mantissa[i] = multiplicand_arr[i+9];
    }
    for(int i = 0; i < 23; i++) {
        M += mantissa[i]*(1/(pow(2, i+1)));
    }
    M = M + 1.0;

    double multiplicand = ldexp(M, E);
    multiplicand = sign ? -multiplicand: multiplicand;
    //printf("multiplicand = %f\n", multiplicand);

    float product = multiplier * multiplicand;
    //printf("product = %f\n", product);

    sign = product<0.0;
    printf("%d_",sign);

    double fraction = sign ? -product : product;

    signed short trial_exp = 0; //11 bits, all 0
    signed short bias = (1<<(7)) - 1;
    signed short trial_E = trial_exp - bias;

    while(trial_exp < (1<<8)-1) {
        trial_E = trial_exp - bias;
        if(fraction / pow(2, trial_E) < 2.0) {
            break;
        }
        trial_exp++;
    }

    for ( int exp_index=7; 0<=exp_index; exp_index-- ) {
        bool exp_bit = 1&trial_exp>>exp_index;
        printf("%d",exp_bit);
        //assert (exp_bit == (1&ref_bits>>(exp_index+FRAC_SZ))); // validate your result against the reference
    }
    printf("_");



    int integral = product;
    int integral_2 = integral;

    //int integral_2 = integral;

    float fractional = product - integral;
    if(fractional < 0) {
        fractional = fractional * -1.0;
    }

    bool frac_array[24]; // one extra LSB bit for rounding
    for ( int frac_index=23; 0<=frac_index; frac_index-- ) {
        frac_array[frac_index] = false; // frac set to zero to enable partial credit
    }
    bool integral_array[64]; //64 arbitrary?
    for(int i = 0; i < 64; i++) {
        integral_array[i] = false;
    }
    for(int i = 63; integral != 0; i--) {
        integral_array[i] = integral % 2;
        //printf(" %d ", integral % 2);
        integral = integral / 2;
    }

    //printf("\nINTEGRAL BINARY REPRESENTATION: \n");
    int frac_counter = 23;
    bool start = false;
    //printf("\nintegral array\n");
    for(int i = 0; i < 64; i++) {
       // printf("%d ", integral_array[i]);
    }
    for(int i = 0; i < 64; i++) {
        if(!start && integral_array[i] == 1) {
            start = true;
            continue;
           // printf("%d ", integral_array[i]);
        }
        else if(start) {
            //printf("%d ", integral_array[i]);
            if(frac_counter < 0) {
                break;
            }
            frac_array[frac_counter] = integral_array[i];
            frac_counter--;
        }
    }
    //printf("\n");
    
    bool zero_integral = false;
    if(integral_2 ==0) {
        zero_integral = true;
    }
    bool skip = false;
    if(zero_integral) {
        skip = true;
    }
    for(int frac_index = frac_counter; 0 <= frac_index; frac_index--) {
        if(product == 0.0) {break;}
        double fractional_res = fractional * 2;
        if(skip) {frac_index = frac_index + 1;}
        if(fractional_res >= 1.0) {
            if(skip) {
                skip = false;
            }
            else {
                frac_array[frac_index] = 1;
            }

        }// else {
            //frac_array[frac_index] = 0;
        //}
        if(fractional_res == 1) {
            break;
        }
        integral = fractional_res;
        fractional = fractional_res - integral;
        
    }

    // rounding
    /* ... */
    //printf("\nfrac bits below\n");

    for ( int frac_index=22; 0<=frac_index; frac_index-- ) {
        bool frac_bit = frac_array[frac_index+1]; // skipping the extra LSB bit for rounding
        printf("%d", frac_bit);
        //assert (frac_bit == (1&ref_bits>>frac_index)); // validate your result against the reference
    }
    // first, read the binary number representation of multiplier
    /* ... */

    // notice that you are reading two different lines; caution with reading
    /* ... */

    // first, read the binary number representation of multiplcand
    /* ... */

    //float product = *(float *) &multiplier * *(float *) &multiplicand; // you are not allowed to print from this.
    //unsigned int ref_bits = *(unsigned int *) &product; // you are not allowed to print from this. But you can use it to validate your solution.

    // SIGN
    /* ... */
    //printf("%d_",sign);
    //assert (sign == (1&ref_bits>>(EXP_SZ+FRAC_SZ)));

    // EXP
    // get the exp field of the multiplier and multiplicand
    /* ... */
    // add the two exp together
    /* ... */
    // subtract bias
    /* ... */

    // FRAC
    // get the frac field of the multiplier and multiplicand
    /* ... */
    // assuming that the input numbers are normalized floating point numbers, add back the implied leading 1 in the mantissa
    /* ... */
    // multiply the mantissas
    /* ... */

    // overflow and normalize
    /* ... */

    // rounding
    /* ... */

    // move decimal point
    /* ... */

    // PRINTING
    // print exp
   /* for ( int bit_index=EXP_SZ-1; 0<=bit_index; bit_index-- ) {
        bool trial_bit = 1&exp>>bit_index;
        printf("%d",trial_bit);
        assert (trial_bit == (1&ref_bits>>(bit_index+FRAC_SZ)));
    }
    printf("_");

    // print frac
    for ( int bit_index=FRAC_SZ-1; 0<=bit_index; bit_index-- ) {
        bool trial_bit = 1&frac>>bit_index;
        printf("%d",trial_bit);
        assert (trial_bit == (1&ref_bits>>(bit_index)));
    }
*/
    return(EXIT_SUCCESS);

}
