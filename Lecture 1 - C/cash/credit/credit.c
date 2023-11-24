#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

// ; at end of line
// () for if
// == for conditions
// {} after else, esp. when empty or multiple lines of instructions


string get_number(void);
string check_card_type(string);
bool check_card_validity(string);
int get_length(string);

int main(void) 
{
    while (true) { 
        string number=get_number();  
            string card_type= check_card_type(number);
            if (get_length(card_type)==0){
            printf("INVALID TYPE\n");   
            }else printf("%s\n", card_type);
    }
}

int get_length(string number)
{
    int n=0; 
    while (number[n]!='\0')  
    { 
        n++;
    }  
    //this function can be replaced by int n = strlen(name) if including string.h in the head
    return n; 
}

string get_number(void)
{
    string number;
    int length;
    do {
        number=get_string("PLease enter credit card number: ");
        length=get_length(number);
    } while (length!=13 && length!=15 && length!=16); 
    return number;
} 
 

bool check_card_validity(string number)
{
    int length=get_length(number);
    int number_as_array[length];
    int n=0;
    while (number[n]!='\0'){ 
        number_as_array[n]=(int)(number[n])-48;
        n++;
    }  
    //printf("%i\n", number_as_array[0]);
    
    int sum1=0;
    for (int n=length-2;n>=0;n=n-2){
        sum1=sum1+(number_as_array[n]*2);  
    } 

    int sum2=0;
    for (int n=length-1;n>=0;n=n-2){
        sum2=sum2+number_as_array[n]; 
    } 
    int sum=sum1+sum2;

    if (sum%10 == 0)
        return true;
    else 
        return false;
}
    
     
string check_card_type(string number)
{
    int length=get_length(number); 
    string card_type="";
    //if 15 digit AND start with 34 or 37 AMEX
    if (length==15) {
        if (number[0]=='3' && (number[1]=='4' || number[1]=='7')){
            card_type="AMEX";
        } 
    }else {
        bool validity = check_card_validity(number);
        if (!validity){
            printf("INValid\n");
        }
        if (length==13) {
            if (number[0]=='4'){
                card_type="VISA";
            } 
        }
        /* if 16 digit
            if starts with 4 VISA
            else MasterCard */
        else if (length==16) {
            if (number[0]=='4'){
                card_type="VISA";
            }else card_type="MASTERCARD";
        }
        
    } 
    return card_type;
} 
