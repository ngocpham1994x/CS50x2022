#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Max number of candidates
#define MAX 9
#define MAX_LENGTH 100

// Candidates have name and vote count
typedef struct
{
    char* name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;


// Function prototypes
bool vote(char* name);
void print_winner(void);

int main(int argc, char* argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        exit(EXIT_FAILURE);
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    // Number of voters
    char voters[MAX_LENGTH];
    printf("Number of voters: ");
    fgets(voters, sizeof(voters), stdin);
    int voter_count = atoi(voters);

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        char name[MAX_LENGTH];
        printf("Vote: ");
        fgets(name, sizeof(name), stdin);

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(char* name)
{
    bool valid = false;

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            valid = true;
            break;
        }
    }

    return valid;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max = candidates[0].votes;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max)
            max = candidates[i].votes;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max)
            printf("%s\n", candidates[i].name);
    }
}