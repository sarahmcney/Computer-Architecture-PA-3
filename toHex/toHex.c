#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int compare(char a[], char b[]);
int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // first, read the number
    signed short int input;
    fscanf(fp, "%hd", &input); // note how the 'h' modifier shortens the %d to half size
    //char binary;

    // print bits; you will see this kind of for loop often in this assignment

    char hex_0[5] = "0000";
    char hex_1[5] = "0001";
    char hex_2[5] = "0010";
    char hex_3[5] = "0011";
    char hex_4[5] = "0100";
    char hex_5[5] = "0101";
    char hex_6[5] = "0110";
    char hex_7[5] = "0111";
    char hex_8[5] = "1000";
    char hex_9[5] = "1001";
    char hex_A[5] = "1010";
    char hex_B[5] = "1011";
    char hex_C[5] = "1100";
    char hex_D[5] = "1101";
    char hex_E[5] = "1110";
    char hex_F[5] = "1111";

    bool binary[17];
    for ( int digit=16; 0<=digit; digit-- ) {
        bool char_val = 0b1 & input>>digit; // shift and mask
        binary[digit] = char_val;
    }
    char byte1[5];
    byte1[4] = '\0';
    for(int i = 0; i < 4; i++) {
        if(binary[i+12] == 1) {
            byte1[3-i] = '1';
        }
        else {
            byte1[3-i] = '0';
        }
    }

    char byte2[5];
    byte2[4] = '\0';
    for(int i = 0; i < 4; i++) {
        if(binary[i+8] == 1) {
            byte2[3-i] = '1';
        }
        else {
            byte2[3-i] = '0';
        }
    }
    
    char byte3[5];
    byte3[4] = '\0';
    for(int i = 0; i < 4; i++) {
        if(binary[i+4] == 1) {
            byte3[3-i] = '1';
        }
        else {
            byte3[3-i] = '0';
        }
    }

    char byte4[5];
    byte4[4] = '\0';
    for(int i = 0; i < 4; i++) {
        if(binary[i] == 1) {
            byte4[3-i] = '1';
        }
        else {
            byte4[3-i] = '0';
        }
    }

    char hex[5];
    if(compare(byte1, hex_0) == 0) { 
        hex[0] = '0';
    }
    if(compare(byte1, hex_1) == 0) { 
        hex[0] = '1';
    }
    if(compare(byte1, hex_2) == 0) { 
        hex[0] = '2';
    }
    if(compare(byte1, hex_3) == 0) { 
        hex[0] = '3';
    }
    if(compare(byte1, hex_4) == 0) { 
        hex[0] = '4';
    }
    if(compare(byte1, hex_5) == 0) { 
        hex[0] = '5';
    }
    if(compare(byte1, hex_6) == 0) { 
        hex[0] = '6';
    }
    if(compare(byte1, hex_7) == 0) { 
        hex[0] = '7';
    }
    if(compare(byte1, hex_8) == 0) { 
        hex[0] = '8';
    }
    if(compare(byte1, hex_9) == 0) { 
        hex[0] = '9';
    }
    if(compare(byte1, hex_A) == 0) { 
        hex[0] = 'A';
    }
    if(compare(byte1, hex_B) == 0) { 
        hex[0] = 'B';
    }
    if(compare(byte1, hex_C) == 0) { 
        hex[0] = 'C';
    }
    if(compare(byte1, hex_D) == 0) { 
        hex[0] = 'D';
    }
    if(compare(byte1, hex_E) == 0) { 
        hex[0] = 'E';
    }
    if(compare(byte1, hex_F) == 0) { 
        hex[0] = 'F';
    }

    if(compare(byte2, hex_0) == 0) { 
        hex[1] = '0';
    }
    if(compare(byte2, hex_1) == 0) { 
        hex[1] = '1';
    }
    if(compare(byte2, hex_2) == 0) { 
        hex[1] = '2';
    }
    if(compare(byte2, hex_3) == 0) { 
        hex[1] = '3';
    }
    if(compare(byte2, hex_4) == 0) { 
        hex[1] = '4';
    }
    if(compare(byte2, hex_5) == 0) { 
        hex[1] = '5';
    }
    if(compare(byte2, hex_6) == 0) { 
        hex[1] = '6';
    }
    if(compare(byte2, hex_7) == 0) { 
        hex[1] = '7';
    }
    if(compare(byte2, hex_8) == 0) { 
        hex[1] = '8';
    }
    if(compare(byte2, hex_9) == 0) { 
        hex[1] = '9';
    }
    if(compare(byte2, hex_A) == 0) { 
        hex[1] = 'A';
    }
    if(compare(byte2, hex_B) == 0) { 
        hex[1] = 'B';
    }
    if(compare(byte2, hex_C) == 0) { 
        hex[1] = 'C';
    }
    if(compare(byte2, hex_D) == 0) { 
        hex[1] = 'D';
    }
    if(compare(byte2, hex_E) == 0) { 
        hex[1] = 'E';
    }
    if(compare(byte2, hex_F) == 0) { 
        hex[1] = 'F';
    }
    
    if(compare(byte3, hex_0) == 0) { 
        hex[2] = '0';
    }
    if(compare(byte3, hex_1) == 0) { 
        hex[2] = '1';
    }
    if(compare(byte3, hex_2) == 0) { 
        hex[2] = '2';
    }
    if(compare(byte3, hex_3) == 0) { 
        hex[2] = '3';
    }
    if(compare(byte3, hex_4) == 0) { 
        hex[2] = '4';
    }
    if(compare(byte3, hex_5) == 0) { 
        hex[2] = '5';
    }
    if(compare(byte3, hex_6) == 0) { 
        hex[2] = '6';
    }
    if(compare(byte3, hex_7) == 0) { 
        hex[2] = '7';
    }
    if(compare(byte3, hex_8) == 0) { 
        hex[2] = '8';
    }
    if(compare(byte3, hex_9) == 0) { 
        hex[2] = '9';
    }
    if(compare(byte3, hex_A) == 0) { 
        hex[2] = 'A';
    }
    if(compare(byte3, hex_B) == 0) { 
        hex[2] = 'B';
    }
    if(compare(byte3, hex_C) == 0) { 
        hex[2] = 'C';
    }
    if(compare(byte3, hex_D) == 0) { 
        hex[2] = 'D';
    }
    if(compare(byte3, hex_E) == 0) { 
        hex[2] = 'E';
    }
    if(compare(byte3, hex_F) == 0) { 
        hex[2] = 'F';
    }

    if(compare(byte4, hex_0) == 0) { 
        hex[3] = '0';
    }
    if(compare(byte4, hex_1) == 0) { 
        hex[3] = '1';
    }
    if(compare(byte4, hex_2) == 0) { 
        hex[3] = '2';
    }
    if(compare(byte4, hex_3) == 0) { 
        hex[3] = '3';
    }
    if(compare(byte4, hex_4) == 0) { 
        hex[3] = '4';
    }
    if(compare(byte4, hex_5) == 0) { 
        hex[3] = '5';
    }
    if(compare(byte4, hex_6) == 0) { 
        hex[3] = '6';
    }
    if(compare(byte4, hex_7) == 0) { 
        hex[3] = '7';
    }
    if(compare(byte4, hex_8) == 0) { 
        hex[3] = '8';
    }
    if(compare(byte4, hex_9) == 0) { 
        hex[3] = '9';
    }
    if(compare(byte4, hex_A) == 0) { 
        hex[3] = 'A';
    }
    if(compare(byte4, hex_B) == 0) { 
        hex[3] = 'B';
    }
    if(compare(byte4, hex_C) == 0) { 
        hex[3] = 'C';
    }
    if(compare(byte4, hex_D) == 0) { 
        hex[3] = 'D';
    }
    if(compare(byte4, hex_E) == 0) { 
        hex[3] = 'E';
    }
    if(compare(byte4, hex_F) == 0) { 
        hex[3] = 'F';
    }
    hex[4] = '\0';
    bool leadingzero = true;

    for(int i = 0; i < 4; i++) {
        if(leadingzero && hex[i] == '0') {
            continue;
        }
        if(leadingzero && hex[i] != '0') {
            leadingzero = false;
        }
        printf("%c", hex[i]);
    }
    return EXIT_SUCCESS;

}

int compare(char a[], char b[]) {
    int c = 0;
    while(a[c] == b[c]) {
        if(a[c] == '\0' || b[c] == '\0') {
            break;
        }
        c++;
    }
    if(a[c] == '\0' && b[c] == '\0') {
        return 0;
    } else {return -1;}
}
