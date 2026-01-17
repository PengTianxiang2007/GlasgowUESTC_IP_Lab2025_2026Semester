#include <stdio.h>
#include <string.h>
#include <ctype.h>

static const char *MORSE_AZ[26] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", 
    ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", 
    ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};
static const char *MORSE_09[10] = {
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---.."
    , "----."
};

int main(){
    char inText[256];
    char outMorse[4096] = "";

    gets(inText);    // Read input line,and store it in the inText array,which is a character array of size 256.  in stdio.h

    if (strlen(inText) == 0) {   //the output type of strlen is size_t type 
        puts(outMorse);    //strlen: calculate the length(number of characters) of the input string
        return 0;      //if you just press enter without typing anything, output empty line
    }

    int is_only_spaces = 1;    //flag to check if input is only spaces
    for (int i = 0; inText[i] != '\0'; i++) { //check each character until the null terminator is reached
        if (!isspace(inText[i])) { 
            is_only_spaces = 0; 
            break;             //check all characters to see if they are all spaces
        }       //as long as one non-space character is found,set the flag to 0 and break the loop
    }

    if (is_only_spaces) {  //if input is only spaces,is_only_spaces remains 1 and we output empty line
        puts(outMorse); 
        return 0;       //if input is only spaces, output empty line
    }

    for (int i = 0; inText[i] != '\0' ; i++)
    {
        char c = inText[i];
        if (isspace(c) || isalnum(c)||c == ';' || c == ':' || c == '-' || c == '!' ||
         c == '?' || c == '.' || c == '\''|| c == ','|| c == '"')  
            continue;
        puts("ERROR");
        return 0;
    }                    //check every character and output ERROR if invalid character found

           //isspace:if the character is one of the six standard whitespace characters,return 1,the type of the return value is int
           //isalnum:if the character is a letter or a digit,return 1         

    // Encoding process
    

    int is_encoded = 0; //flag to track if any valid character has been encoded,
                        //to solve the problem of leading spaces

    for (int i = 0; inText[i] != '\0' ; i++)
    {
        char c = inText[i];  //c:store the ASCII value of the current character
        c = toupper(c);        //convert to uppercase for uniformity
                    //the return value of toupper is int type,but it can be safely assigned to char type

        if (c >= 'A' && c <= 'Z') {  
            int index = c - 'A';      //char type are turned into int type for calculation
            strcat(outMorse, MORSE_AZ[index]);   //append Morse code for the letter
    //to check if we need to add a space after the Morse code,the return value of strcat is the initial address of the string
            int j = i + 1;    //if there is punctuation between letters/numbers,we need to add a space
            while (inText[j] != '\0' && (inText[j]==','||inText[j]=='.'||inText[j]=='!'||inText[j]=='?'||
                                 inText[j]==';'||inText[j]==':'||inText[j]=='-'||inText[j]=='"'||inText[j]=='\''))
                j++;   //if the next character(s) are punctuation,skip them,and do not add "/",only add space
                       //finish the loop when a non-punctuation character or null terminator is found
                       //if j is at a number,letter,out the loop
            if (inText[j] != '\0' && !isspace(inText[j])) //unless two special cases,add space
                strcat(outMorse, " ");   
                            

            is_encoded = 1;      //set flag to indicate encoding has occurred

        } else if (c >= '0' && c <= '9') {
            int index = c - '0';
            strcat(outMorse, MORSE_09[index]);

            int j = i + 1;
            while (inText[j] != '\0' && (inText[j]==','||inText[j]=='.'||inText[j]=='!'||inText[j]=='?'||
                                 inText[j]==';'||inText[j]==':'||inText[j]=='-'||inText[j]=='"'||inText[j]=='\'')) j++;
            if (inText[j] != '\0' && !isspace(inText[j])) 
                strcat(outMorse, " ");

            is_encoded = 1;

        } else if (c == ';' || c == ':' || c == '-' || c == '!' || c == '?' || c == '.' || c == '\''|| c == ','|| c == '"') {
            continue;  //skip punctuation characters
        } else if (isspace(c)) {//to avoid the continus "/" by examineing the previous character
            if (i > 0) {                        //make sure i-1 is valid
                if (!isspace(inText[i-1])) {    //check whether the previous character was not a space
                    if (is_encoded == 1) {      //make sure the "/" will not be added at the beginning
                        strcat(outMorse, "/");   //add "/" to separate words
                    }
                }
            }
        }
    }

    int final_len = strlen(outMorse);//to locate the last character because if it only appear once if it's "/"
    if (final_len > 0) {
        char last_char = outMorse[final_len - 1];//locate the last character and check if it is space or "/"
        if (last_char == ' ' || last_char == '/') {
            outMorse[final_len - 1] = '\0'; //remove it by replacing with null terminator
        }
    }                //remove the "/" or space at the end if present

    puts(outMorse);
    return 0;
}
