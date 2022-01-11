#ifndef RAM__H
#define RAM__H

typedef struct ram_t {
    unsigned int * buff;
} ram_t;

ram_t * RAM_set(unsigned int * buff);
char RAM_get_byte(const ram_t *ram, unsigned int address);
unsigned int RAM_get_word(const ram_t *ram, unsigned int address);
void RAM_set_byte(ram_t *ram, char data, unsigned int addres);
void RAM_set_word(ram_t *ram, unsigned int data, unsigned int addres);
void RAM_get_words(const ram_t *ram, unsigned int *buffer, unsigned int address, unsigned int count);
void RAM_set_words(ram_t *ram, const unsigned int *buffer, unsigned int address, unsigned int count);

#endif
