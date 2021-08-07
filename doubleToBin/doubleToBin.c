#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 11
#define FRAC_SZ 52

int main(int argc, char *argv[]) {

    // SETUP

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    double value;
    fscanf(fp, "%lf", &value);
    //printf("%lf\n", value);

    // the reference solution ('the easy way')
    // you are not allowed to print from this casted 'ref_bits' variable below
    // but, it is helpful for validating your solution
    unsigned long int ref_bits = *(unsigned long int*) &value;

    // THE SIGN BIT
    bool sign = value<0.0;
    printf("%d_",sign);
    assert (sign == (1&ref_bits>>(EXP_SZ+FRAC_SZ))); // validate your result against the reference

    // THE EXP FIELD
    // find the exponent E such that the fraction will be a canonical fraction:
    // 1.0 <= fraction < 2.0
    double fraction = sign ? -value : value;
    //printf("fraction = %lf\n", fraction);

    signed short trial_exp = 0; //11 bits, all 0
    signed short bias = (1<<(EXP_SZ-1)) - 1;
    signed short trial_E = trial_exp - bias;
    //printf("bias = %hi\n", bias);
    //printf("trial_E = %hi\n", trial_E);

    while(trial_exp < (1<<EXP_SZ)-1) {
        trial_E = trial_exp - bias;
        if(fraction / pow(2, trial_E) < 2.0) {
            break;
        }
        trial_exp++;
    }
    //printf("trial_exp = %hi\n", trial_exp);

    for ( int exp_index=EXP_SZ-1; 0<=exp_index; exp_index-- ) {
        bool exp_bit = 1&trial_exp>>exp_index;
        printf("%d",exp_bit);
        //assert (exp_bit == (1&ref_bits>>(exp_index+FRAC_SZ))); // validate your result against the reference
    }
    printf("_");
    // you get partial credit by getting the exp field correct
    // even if you print zeros for the frac field next
    // you should be able to pass test cases 0, 1, 2, 3

    // THE FRAC FIELD
    // prepare the canonical fraction such that:
    // 1.0 <= fraction < 2.0
    /* ... */

   

    bool frac_array[FRAC_SZ+1];
    for ( int frac_index=FRAC_SZ; 0<=frac_index; frac_index-- ) {
        frac_array[frac_index] = false; // frac set to zero to enable partial credit
    }
    
    double mantissa = (trial_exp == 0.0) ? fraction / (pow(2, (1.0 - bias))) : (fraction / (pow(2, (trial_exp - bias)))) - 1.0;
    
    for(int i = 0; i < FRAC_SZ+1; i++) {
        mantissa = mantissa * 2;
        int integer_mantissa = mantissa;
        if(integer_mantissa >= 1) {
            frac_array[FRAC_SZ - i] = true;
        } else {
            frac_array[FRAC_SZ - i] = false;
        }
        mantissa = mantissa - integer_mantissa;
    }

    

    // rounding
    /* ... */
    //printf("\nfrac bits below\n");

    for ( int frac_index=FRAC_SZ-1; 0<=frac_index; frac_index-- ) {
        bool frac_bit = frac_array[frac_index+1]; // skipping the extra LSB bit for rounding
        printf("%d", frac_bit);
        //assert (frac_bit == (1&ref_bits>>frac_index)); // validate your result against the reference
    }

}
