#include "../lazer.h"

void run(const char *target) 
{
    srand(time(NULL));

    FILE *f = fopen(target, "r+");
    if (!f) {
        perror("TARGET ESCAPED");
        return;
    }
    int c;
    while ((c = fgetc(f)) != EOF) 
    {
        fseek(f, -1, SEEK_CUR);
        fputc(c ^ (rand() % 256), f);
        fflush(f);
    }

    fclose(f);
    printf("[BROADCAST FROM MISSILE] ::: [%s] has been “corrupted”\n", target);
}