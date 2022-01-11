#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "ram.h"
#include "memutils.h"


// falta checkear limites!
// y todo eso


ram_t * RAM_set(unsigned int * buff) {
    ram_t *ram = malloc(sizeof(ram_t));
    ram->buff = buff;
    return ram;
}

char RAM_get_byte(const ram_t *ram, unsigned int address) {
    int c = ram->buff[address/4];
    c = htonl(c);
    //rapido no?
    int offset = address%4;
    switch (offset)
    {
    case 0/* constant-expression */:
        c = c & 0x000000ff;
        break;
    case 1/* constant-expression */:
        c = (c & 0x0000ff00) >> 8;
        break;
    case 2/* constant-expression */:
        c = (c & 0x00ff0000) >> 16;
        break;
    case 3/* constant-expression */:
        c = (c & 0xff000000) >> 24;
        break;
                
    default:
        break;
    }

    return (char)c;
}

unsigned int RAM_get_word(const ram_t *ram, unsigned int address) {
    return ram->buff[address/4];
}

void RAM_get_words(const ram_t *ram, unsigned int *buffer, unsigned int address, unsigned int count) {
    for(int i=0; i<count; i++) {
        buffer[i] = ram->buff[address/4+i];
    }  
}

void RAM_set_words(ram_t *ram, const unsigned int *buffer, unsigned int address, unsigned int count) {
    for(int i=0; i<count; i++) {
        ram->buff[address/4+i] = buffer[i];
    }
    printf("DEBUG: RAM WRITE");
    MEMUTILS_ram_print(ram, address, count, NULL);
}


void RAM_set_byte(ram_t *ram, char data, unsigned int address) {
    int c = ram->buff[address/4];
    int idata = c;
    
    c = htonl(c);
    //rapido no?
    int offset = address%4;
    
    switch (offset)
    {
    case 0/* constant-expression */:
        c &= ~0x000000ff;
        c |= idata;
        break;
    case 1/* constant-expression */:
        c &= ~0x0000ff00;
        c |= (idata << 8);
        break;
    case 2/* constant-expression */:
        c &=  ~0x00ff0000;
        c |= (idata << 16);
        break;
    case 3/* constant-expression */:
        c &= ~0xff000000;
        c |= (idata << 24);
        break;
                
    default:
        break;
    }

    ram->buff[address/4] = ntohl(c);
    
}

void RAM_set_word(ram_t *ram, unsigned int data, unsigned int address) {
    ram->buff[address/4] = data;
}