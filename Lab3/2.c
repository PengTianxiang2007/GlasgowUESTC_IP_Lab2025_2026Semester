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

    gets(inText);

    if (strlen(inText) == 0) {
    puts(outMorse); 
    return 0;      
}

    int is_only_spaces = 1; 
for (int i = 0; inText[i] != '\0'; i++) {
    if (!isspace(inText[i])) { 
        is_only_spaces = 0; 
        break;             
    }
}

if (is_only_spaces) {
    puts(outMorse); 
    return 0;       
}

for (int i = 0; inText[i] != '\0' ; i++)
{
        char c = inText[i];
        if (isspace(c) || isalnum(c)||c == ';' || c == ':' || c == '-' || c == '!' || c == '?' || c == '.' || c == '\''|| c == ','|| c == '"')
        continue;
        puts("ERROR");
        return 0;
    }

    int is_encoded = 0;

for (int i = 0; inText[i] != '\0' ; i++)
{
    char c = inText[i];
    c = toupper(c);

    if (c >= 'A' && c <= 'Z') {
            int index = c - 'A';
            strcat(outMorse, MORSE_AZ[index]);
            if (inText[i+1] != '\0' && !isspace(inText[i+1])&&inText[i+1] != ','&&inText[i+1] != '.'&&inText[i+1] != '!'&&inText[i+1] != '?'&&inText[i+1] != ';'&&inText[i+1] != ':'&&inText[i+1] != '-'&&inText[i+1] != '"'&&inText[i+1] != '\'') 
                strcat(outMorse, " ");   
            is_encoded = 1;      
    } else if (c >= '0' && c <= '9') {
            int index = c - '0';
            strcat(outMorse, MORSE_09[index]);
            if (inText[i+1] != '\0' && !isspace(inText[i+1])&&inText[i+1] != ','&&inText[i+1] != '.'&&inText[i+1] != '!'&&inText[i+1] != '?'&&inText[i+1] != ';'&&inText[i+1] != ':'&&inText[i+1] != '-'&&inText[i+1] != '"'&&inText[i+1] != '\'') 
                strcat(outMorse, " ");
            is_encoded = 1;
    } else if (c == ';' || c == ':' || c == '-' || c == '!' || c == '?' || c == '.' || c == '\''|| c == ','|| c == '"') {
            continue;
    } else if (isspace(c)) {
    if (i > 0) {
        if (!isspace(inText[i-1])) { 
            if (is_encoded == 1) {
                strcat(outMorse, "/");
            }
        }
    }

    }
}

int final_len = strlen(outMorse);
if (final_len > 0) {
    char last_char = outMorse[final_len - 1];
    
    if (last_char == ' ' || last_char == '/') {
        outMorse[final_len - 1] = '\0'; 
    }
}
    puts(outMorse);
    return 0;

}