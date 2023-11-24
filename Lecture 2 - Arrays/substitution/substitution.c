#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool repetition(string);
char encipher(char);
string key; 

int main(int argc, string argv[]) 
{
        //GET A KEY 
    //argc must be 2  
    if (argc!=2) {
        if (argc==1){printf("Type key in command line.\n");
        }else{
            printf("Type one key only\n");
        } 
        return 1;
    }
    key=argv[1];  
        
        //VALIDATE KEY  
    int i=0;
    if((strlen(key))!=26){
        printf("key must contain 26 characters\n");
        return 1;
    }else{ 
        while(i<26)
        { 
            if (!isalpha(key[i])) {
            printf("key must only contain alphabetic characters\n");
            return 1;
            } else{
                i++;
            } 
        }
    }

    if (repetition(key)){
        printf("key must not contain repeated characters\n");
        return 1;
    }else{
        //GET PLAINTEXT
        string plain_text=get_string("plaintext: ");
        printf("ciphertext: ");


            //ENCIPHER  

        int plain_text_length=strlen(plain_text);
        i=0;  
        string enciphered_plain_text;
        while(i<plain_text_length){
            if((plain_text[i]>64 && plain_text[i]<91) || (plain_text[i]>96 && plain_text[i]<123)){ 
                enciphered_plain_text[i]=encipher(plain_text[i]);}else{
                    enciphered_plain_text[i]=plain_text[i]; //special characters must stay unchanged
                }
            
            printf("%c", enciphered_plain_text[i]);
            i++; 
        }
    } 

    printf("\n"); 
}


bool repetition(string word){ 
    int i=0;
    int j=1;
    int length=strlen(word);
    if(length==0){
        return false;
    } 
    while(i<length-1){
        while(j<length){ 
            if(tolower(word[i])==tolower(word[j])){  
                return true;
            }
            j++;
        }  
        i++;
        j=i+1;
    } 
    return false;
}

char encipher(char letter){ 
    //printf("%s", key);
    int i;
    char enciphered_letter;
    if((letter>64 && letter<91)){
        i=letter-65;
        key[i]=toupper(key[i]);
        //printf("%i", i);
    }else{
        i=letter-97; 
        key[i]=tolower(key[i]); 
    } 
    //printf("%c", key[i]);
    enciphered_letter=key[i];  
    return enciphered_letter;  
} 