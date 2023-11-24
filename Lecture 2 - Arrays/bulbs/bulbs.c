#include <cs50.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
int* make_decimal(string);
int* make_binary(int);

int main(void)
{
    // prompt for word
    string word = get_string("Enter word: ");
    
    //turning text into decimal number with ASCII
    //string word[strlen(word)];
   
    int *decimal_word=make_decimal(word);
    
    int length = strlen(word); 

    int *binary_word[length]; 
    for (int i = 0; i<length; i++) //turning decimal number into a series of 8-bit binary numbers, one for each character of the string.
    { 
        binary_word[i]=make_binary(decimal_word[i]);
        //printf("%d\n", binary_word[i][0]);
        //printf("%d\n", decimal_word[i]);
    }
    free(decimal_word);

    for (int i = 0; i<length; i++){ //for each letter 
        int *binary_letter=binary_word[i];
        for (int j = 0; j<BITS_IN_BYTE; j++){ //for each bit 
            print_bulb(binary_letter[j]);
        } 
        free(binary_letter);
        printf("\n");    //there should be a \n after the last “byte” of 8 symbols as well.
    }
    free(binary_word);
}


int* make_decimal(string word){
    int length=strlen(word);
    int *decimal_word=malloc(length*sizeof(int));
    for (int i = 0; i<length; i++)
    {
        decimal_word[i]=(int)word[i]; 
    }
    return decimal_word;
}

int powp(int base, int p){
    int result=1;
    for(int i=0; i<p; i++){
        result*=base;
    }
    return result;
}

int* make_binary(int decimal_letter){  
    int *binary_letter=malloc(8*sizeof(int));  
        for (int p = 7;p>=0; p--){ 
            //printf("%d\n", (powp(2, p)));
            if (decimal_letter >= powp(2, p)){
                binary_letter[7-p]=1;
                decimal_letter-=powp(2, p);
            }else{
                binary_letter[7-p]=0; 
            }
        } 
    return binary_letter;
}

void print_bulb(int bit)
{
    //printf("%d",bit);
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
