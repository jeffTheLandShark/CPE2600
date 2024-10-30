#include <stdlib.h>

// Some "global" data arrays
const char *help[] = {"Help text line 1","Help text line 2","More help
text",""};
const char info[][4] = {"NUL","BEL","EOR","FUN","END"}; // why 4?


// note, argv is often char**, what is that? A double pointer?
int main(int argc, char* argv[]) {
    // print out arrays
    int i = 0;
    while (strlen(help[i])) {
        // help is an array of char*...
        printf("Line %d: %s\n",i,help[i]);
        i++;
    }
    // if using 2 indexes, get a character
    printf("Info [%d][%d]: %c\n",1,1,info[1][1]);
    // if using 1 index, you will basically get
    // the address to the first element of that
    // row. In this case, that is actaully char*
    // and can use it like a string.
    printf("Info %d: %s\n",1,info[1]);
    // OK, I said stay away from sizeof, but I cannot resist
    printf("Sizeof Help: %zu\n",sizeof(help));
    printf("Sizeof Info: %zu\n",sizeof(info));
    // Hmm...
    printf("Address of help[0]: %p\n",&help[0]);
    printf("Address of help[1]: %p\n",&help[1]);
    printf("Address of info[0]: %p\n",&info[0][0]);
    printf("Address of info[1]: %p\n",&info[1][0]);
    return 0;
}