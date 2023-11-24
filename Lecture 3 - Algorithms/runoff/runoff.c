#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            } 
        }
        printf("\n");
    } 


    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        /* for (int k = 0; k < candidate_count; k++)
        { 
            printf("%s has %i votes\n", candidates[k].name, candidates[k].votes);
        } */

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}


bool vote(int voter, int rank, string name)// Record preference if vote is valid
{   
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcmp(candidates[k].name, name)==0)//if name is a match for the name of a valid candidate
            {
                preferences[voter][rank]=k;//update global preferences array with the index of the candidate who is the jth ranked preference for the ith voter. 
                return true;
            }
    }
        return false;//if invalid vote
} 


void tabulate(void)// Tabulate votes for non-eliminated candidates
{
    // TODO: look at all of the voters’ preferences and compute the current vote totals, 
    //by looking at each voter’s top choice candidate who hasn’t yet been eliminated 
    for (int i = 0; i < voter_count; i++)//for each voter
    {  
        int j=0;  
        while(candidates[preferences[i][j]].eliminated)//take 1st non-eliminated preference
        {  
            j++;
        } 

        candidates[preferences[i][j]].votes=candidates[preferences[i][j]].votes+1;
    }
    return;
}

bool print_winner(void)// Print the winner of the election, if there is one
{ 
    for (int k = 0; k < candidate_count; k++)//for each candidate
        {
            if((candidates[k].votes)>(voter_count/2))//if candidate has more than half of the vote, wins 
            { 
                printf("%s wins!\n", candidates[k].name);
                return true; 
            }
        }   
    return false;
}

int find_min(void)// Return the minimum number of votes any remaining candidate has
{
    int min=voter_count*voter_count;  //set min to max number of votes
    for (int k = 0; (k < candidate_count); k++)//for each candidate
    {
        if(candidates[k].eliminated==false&&(candidates[k].votes<min))
        {
            min=candidates[k].votes;
        }
    }
    printf("%i\n", min);
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    // if true,  the election is declared a tie, exit
    /* for (int k = 0; k < candidate_count; k++)//for each candidate
        {
            if(candidates[k].votes
        }   
    return false; */
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int k = 0; (k < candidate_count-1); k++)//for each candidate
        {
            if(candidates[k].votes==min)
            {
                candidates[k].eliminated=true;
                printf("%s is eliminated!\n", candidates[k].name);
            } 
        } 
    return;
}