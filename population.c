#include <cs50.h>
#include <stdio.h>
int get_start_size(void); 
int get_end_size(void);
int calculate_years(int, int);

int main(void)
{
    //Prompt for start size 
    int start_size=get_start_size();
    
    //Prompt for end size 
    int end_size=get_end_size();

    //Calculate number of years until we reach threshold 
    int years=calculate_years(start_size, end_size);

    //Print number of years
    printf("It will take %i years for the population of llamas to reach %i\n", years, end_size);
}


int get_start_size(void)
    {
        int start_size;
            do 
        {
                start_size = get_int("How many llamas are there to start with? "); 
        }  
            while (start_size<9);
            
            return start_size;
    }

int get_end_size(void)
{
    int end_size;
    int start_size;//necessary??
        do 
    {
            end_size = get_int("How many llamas will there be in the end? "); 
    }  
        while (end_size<start_size);
        
        return end_size;
}

int calculate_years(end_size, start_size)
{
    int years;
    years=(end_size)/((start_size+(start_size/3)-(start_size/4))-(start_size));
    return years;
} 