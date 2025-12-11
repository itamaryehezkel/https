#ifndef ITL_H
#define ITL_H

#include "xxhash.h"
#include "structs.h"
#include "pp.c"
#include "tokens.c"
#include "parser.c"
#include "ast.c"

Token * tokens;
char * itlc;
Node * program; // = parse_program(tokens, itlc);
/*
cat ~/.bash_profile
cat ~/.bash_login
cat ~/.profile
cat ~/.bashrc
sudo grep -r "Last login" /etc/
sudo grep -r "lastlog" /home/itamar/

*/

unsigned char * load_itl(){
    fprintf(stdout, "\e[90mLoaded ITLC from: %s\e[0m\n", ITL_C);
    FILE* file = fopen(ITL_C, "r");
    if (!file) {
        perror("Failed to open file");
        return "";
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        perror("fseek failed");
        fclose(file);
        return "";
    }

    long size = ftell(file);
    if (size < 0) {
        perror("ftell failed");
        fclose(file);
        return "";
    }
    rewind(file);

    unsigned char* buffer = (unsigned char*)calloc(size/sizeof(unsigned char), sizeof(unsigned char));;
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return "";
    }

    size_t read = fread(buffer, 1, size, file);
    fclose(file);

    if (read != (size_t)size) {
        fprintf(stderr, "Only read %zu of %ld bytes\n", read, size);
        free(buffer);
        return "";
    }

    return buffer;
}

void load_program(){
    itlc = load_itl();
    tokens = tokenise(itlc);
    program = parse_program(tokens, itlc);

}
#endif