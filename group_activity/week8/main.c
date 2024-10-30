//gcc main.c -o imagemaker.exe

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]) {
    FILE *fp;
    FILE *lpi_fp;
    FILE *final_fp;
    char line[500];
    char *filename;
    char *lpi_filename = "lpi_";
    char *final_filename = "final_";

    int height = 0;
    int width = 0;
    char* token;

    // get filename
    if (argc > 1) {
        filename = argv[1];
    } else {
      filename = "cameraman.pgm";
    }
    strcat(lpi_filename, filename);
    strcat(final_filename, filename);
    fp = fopen(filename, "r");
    lpi_fp = fopen(lpi_filename, "w");
    final_fp = fopen(final_filename, "w");

    if(!fp)
    {
        fputs("Error opening file\n", stderr);
        exit(1);
    }

    for (int i = 0; i < 4; i++) {
        fgets(line,500,fp);
        //printf("%s", line);
        if (i == 1) {
            fputs("# Edited by Holden\n", lpi_fp);
            fputs("# Edited by Holden\n", final_fp);
            printf("# Edited by Holden\n");
        } else if (i == 2) {
            fputs(line,lpi_fp);
            fputs(line,final_fp);
            printf("%s", line);

            //get dimensions
            token = strtok(line, " ");
            height = atoi(token);
            token =strtok(NULL, " ");
            width = atoi(token);
        } else {
            fputs(line,lpi_fp);
            fputs(line,final_fp);
            printf("%s", line);
        }
    }
    
    char *original_array = malloc(sizeof(char)*height*width);
    char *lpi_array = malloc(sizeof(char)*height*width);
    char *final_array = malloc(sizeof(char)*height*width);
    //putting values of original image in array
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            *(original_array+i*width+j) = fgetc(fp);
        }
    }

    //making new LPI image and final image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i != 0 && i != (height - 1) && j != 0 && j != (width - 1)) {
                *(lpi_array+i*width+j) = (int) (1.0/9.0 * (
                                        *(original_array+(i-1)*width+j-1) + *(original_array+(i-1)*width+j) + *(original_array+(i-1)*width+j+1) +
                                        *(original_array+(i+0)*width+j-1) + *(original_array+(i+0)*width+j) + *(original_array+(i+0)*width+j+1) +  
                                        *(original_array+(i+1)*width+j-1) + *(original_array+(i+1)*width+j) + *(original_array+(i+1)*width+j+1)
                                        )); 
            } else { //if on border of image, just use original value
                *(lpi_array+i*width+j) = *(original_array+i*width+j);
            }
            *(final_array+i*width+j) = 4 * (*(original_array+i*width+j)) - 3 * (*(lpi_array+i*width+j));
            fputc(*(lpi_array+i*width+j), lpi_fp);
            fputc(*(final_array+i*width+j), final_fp);
        }
    }

    fclose(fp);
    fclose(lpi_fp);
    fclose(final_fp);
    return 0;
}