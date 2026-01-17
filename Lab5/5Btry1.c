#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char filename[20];
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");    //r means read only,the return value is the address of the file

    int frequency[256] = {0};  //store frequency of each pixel value
    int pixelvalue;          
                                                    //2 hexadecimal digits can represent values from 0 to 255
    while(fscanf(file, "%2x", &pixelvalue) != EOF)  //%2x means read two hexadecimal digits every time
    {                       //&pixelvalue means store the read value in pixelvalue 
        frequency[pixelvalue]++;  //read pixel value and add its frequency in the array frequency
    }

    fclose(file);


    int max_freq = 0;
    int best_pixel = 0;
    for(int i = 0; i < 256; i++)
    {
        if(frequency[i] > max_freq)  //find the pixel value with the highest frequency
        {                            //if the number is greater than the former one,then update it
            max_freq = frequency[i];
            best_pixel = i;
        }                            
    }

    FILE *output_file = fopen("output.txt", "a");//a means append the content,do not overwrite the original content

    fprintf(output_file,"%02X %d\n", best_pixel, max_freq);
//02means print at least 2 digits,if less than 2 digits,pad with leading zeros,X means print in uppercase hexadecimal format
    fclose(output_file);

    return 0;
}