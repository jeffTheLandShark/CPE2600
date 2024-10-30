#include <stdio.h>
#include <string.h>

// note, argv is often char**, what is that? A double pointer?
int main(int argc, char* argv[]) {
    printf("Number of args: %d\n",argc);

    for(int i=0; i<argc; i++) {
        printf("Arg %d is %s\n",i,argv[i]);
    }

    // a particular arg
    if(argc>1) {
        if(!strcmp(argv[1],"marco")) {
            printf("Polo\n");
        }
    }
    
    return 0;
}