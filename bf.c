#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int symcount = 0;
int nextsymint = 0;
char **symbols;
char *nextsym = ".L0";

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Usage: bf [FILE] [-o [FILE]]\n");
        return 0;
    }

    /* Open the files */
    FILE *src = fopen(argv[1], "r");
    FILE *dest = (argc >= 4) ? fopen(argv[3], "w") : fopen("a.s", "w");

    symbols = malloc(1);

    fprintf(dest, ".bss\n\t.comm arr, 3000\n.text\nstart:\n\txor %%ecx, %%ecx\n");
    int C;
    while((C = getc(src)) != EOF)
    {
        switch(C)
        {
            case '>':
            fprintf(dest, "\tinc %%ecx\n");
            break;

            case '<':
            fprintf(dest, "\tdec %%ecx\n");
            break;

            case '+':
            fprintf(dest, "\tincb arr(, %%ecx)\n");
            break;

            case '-':
            fprintf(dest, "\tdecb arr(, %%ecx)\n");
            break;

            case '[':
            symcount++;
            symbols = realloc(symbols, sizeof(char*) * symcount);
            symbols[symcount-1] = nextsym;
            nextsymint++;
            nextsym = malloc(snprintf(NULL, 0, ".L%i", nextsymint));
            sprintf(nextsym, ".L%i", nextsymint);
            fprintf(dest, "\txor %%ebx, %%ebx\n\tcmp arr(, %%ecx), %%ebx\n\tje %s\n%s:\n", nextsym, symbols[symcount-1]);
            symcount++;
            symbols = realloc(symbols, sizeof(char*) * symcount);
            symbols[symcount-1] = nextsym;
            nextsymint++;
            nextsym = malloc(snprintf(NULL, 0, ".L%i", nextsymint));
            sprintf(nextsym, ".L%i", nextsymint);
            break;

            case ']':
            fprintf(dest, "\txor %%ebx, %%ebx\n\tcmpb arr(, %%ecx), %%ebx\n\tjne %s\n%s:\n", symbols[symcount-2], symbols[symcount-1]);
            free(symbols[symcount-1]);
            free(symbols[symcount-2]);
            symcount -= 2;
            symbols = realloc(symbols, symcount * sizeof(char*));
            break;

            /* System calls, my favorite */
            case '.':
            #ifdef __linux__
            fprintf(dest, "\tpush %%ecx\n\tmov $0, %%rax\n\tmov $1, %%rdi\n\tlea arr(, %%ecx), %rsi\n\tmov $1, %%rdx\n\tsyscall\n\tpop %%ecx\n");
            #endif
            break;

            case ',':
            #ifdef __linux__
            fprintf(dest, "\tpush %%ecx\n\tmov $1, %%rax\n\tmov $0, %%rdi\n\tlea arr(, %%ecx), %rsi\n\tmov $1, %%rdx\n\tsyscall\n\tpop %%ecx\n");
            #endif
            break;

            default:
            break;
        }
    }
    #ifdef __linux__
    fprintf(dest, "\tmov $60, %%rax\n\txor %%rdi, %%rdi\n\tsyscall");
    #endif
    fclose(dest);

    return 0;
}