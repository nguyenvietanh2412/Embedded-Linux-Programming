#include <stdio.h>

int main(int argc, char *argv[]) {

    if(argc != 3) {
        printf("Valid syntax: <executable file> <filename> <string>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "w");
    if(file == NULL) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    fprintf(file, "%s\n", argv[2]);

    fclose(file);

    return 0;
}
