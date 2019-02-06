#include "coding.h"

unsigned char encode(unsigned char c){

    return c + 10;
}

unsigned char decode(unsigned char c){
    return c - 10;
}