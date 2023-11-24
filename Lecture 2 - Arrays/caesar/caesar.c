#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


bool only_digits(string);
char encipher(char);
int k; 

int main(int argc, string argv[]) 
{
//GET VALID KEY
    //make sure k is a single CL argument
    
    if(argc!=2){
        printf("Usage: ./caesar key");
        return 1; 
    }else{ //make sure k only contains digit characters 
            if(only_digits(argv[1])==false){//if key contains non-digit characters, error message
                printf("key must be digit");
                return 1; 
            }else {//if k digits only, convert it into integer
                k=atoi(argv[1]);  
                //printf("%i", k); //test
            }; 
        }
     
//GET PLAIN TEXT 
    string p=get_string("plaintext: ");   
    printf("ciphertext: ");

//ENCIPHER  
    int i=0;
    string c; 
    int length_of_p=strlen(p);  
    while(i<length_of_p){//check if each character is alphabetic
        if (isalpha(p[i])==false){
            //printf("is not alphabetic");//test 
            printf("%c", p[i]);//if not alphabetic, leave as is 
        }else{//if alphabetic, encipher  
            //printf("is alphabetic");//test
            //c[i]=encipher(p[i]);
            printf("%c", encipher(p[i]));
        }  
        i++;
    } 
    printf("\n");     
}

bool only_digits(string key){ //argv[1] is the key -> inside argv[1], go through every char in string to make sure is digit  only_digits      
    int i=0;
    int length=strlen(key); 
    while(i<length){
        if (!isdigit(key[i])){
            return false;
        }
        i++;
    } return true; 
}

char encipher(char letter){   
    char enciphered_letter;
    int alpha_letter;
    if (islower(letter)){ //changing ASCII to alphabetical index  A(or a)=0 -> Z(or z)=25
        //printf("lowercaseletter");//test
        alpha_letter=letter-97;//(ASCII)a to b = 97 to 122 
        //printf("%i", letter);//test
    }else{
        //printf("uppercaseletter");//test
        alpha_letter=letter-65;//(ASCII)A to Z=65 to 90 
    }
    enciphered_letter = (alpha_letter+k)%26;//c[i]=(p[i]+k)%26
    if (islower(letter)){ //revert to ASCII 
        enciphered_letter=enciphered_letter+97; 
    }else{ 
        enciphered_letter=enciphered_letter+65; 
    }
    return enciphered_letter;//return c[i]
}