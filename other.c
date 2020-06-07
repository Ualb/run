#include <stdio.h>
#include <aio.h>

int main(int argc,  char *argv[]) {
    
    if (argc >= 1) 
    {
        printf("%s\n", argv[1]);
        printf("%s\n", argv[2]);
    }
    else
    {
        printf("programa sencillo");
    }

    return 0;
}