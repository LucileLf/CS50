#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int wordsize = 0;
string key;
char keychar; 
string guess;

#define EXACT 2
#define CLOSE 1
#define WRONG 0

string get_guess(int);
int check_word(string, int, int[], string);

string choice = "frogs";

int main(int argc, string argv[])
{
    // ensure proper usage  
    if (argc!=2){ 
        if (argc==1){
            printf("Usage: ./wordle wordsize\n");
        }else{
            printf("Type one key only\n");
        } 
        return 1; 
    }else{
        key= argv[1];
        if(strlen(key)!=1){
            printf("Error: wordsize must be either 5, 6, 7, or 8");
            return 1;
        }else{ 
            keychar=key[0];
            if (isdigit(keychar)==false){
                        printf("Key must be a digit\n");
            }else{   
                wordsize = atoi(&keychar); 
                if(wordsize<5 || wordsize>8){
                    printf("Error: wordsize must be either 5, 6, 7, or 8");
                    return 1;
                }else{
                    int guesses = wordsize + 1;
                    printf("This is WORDLE50. You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);
                    guess= get_guess(wordsize);

                    // TODO #4: set all elements of status array initially to 0, aka WRONG 
                int status[wordsize]; 
                for(int i=0; i<wordsize; i++){
                    status[i]=WRONG; 
                }
                    
                // Calculate score for the guess
                int score = check_word(guess, wordsize, status, choice);
                if (score==2*wordsize){

                }
                } 
            }
        }
    }  
} 

string get_guess(int wordsize){ 
    string word;
    do {
        word = get_string("Input a %i-letter word: ", wordsize);
    }while(strlen(word)!=wordsize);
    guess=word;
    //printf("%s",guess);
    return guess;
}


int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0; 
    int i;
    int j;
    // compare guess to choice and score points as appropriate, storing points in status
    // TODO #5
    for(i=0; i<wordsize; i++){  
        if(guess[i]==choice[i]){
            status[i]=EXACT; 
        }else{
            for(j=0; j<wordsize; j++){
                if(guess[i]==choice[j]){
                    status[i]=CLOSE; 
                    j=wordsize;              
                }else{
                    status[i]=WRONG;                     
                }
            } 
        } 
    }  

i=0;
while(i<wordsize){
    score+=status[i];
    i++;
}
printf("%i", score);
return score;
}      