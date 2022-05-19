#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9
#define MAX_LENGTH 1000

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    char* name;
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
bool vote(int voter, int rank, char* name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
void bubble_sort(int arr[], int size);
void swap(int* x, int* y);

int main(int argc, char* argv[])
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
            char name[MAX_LENGTH];
            printf("Rank %i: ", j + 1);
            fgets(name, sizeof(name), stdin);

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

// Record preference if vote is valid
bool vote(int voter, int rank, char* name)
{
    bool valid = true;
    int false_count = 0;

    // iterate through the candidates to find name match
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            break;
        }
        else
            false_count++;
    }

    if (false_count == candidate_count)
        valid = false;

    return valid;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int rank;
    int candidate;

    // iterate over voters
    for (int vote = 0; vote < voter_count; vote++)
    {
        rank = 0;
        candidate = preferences[vote][rank];

        if (!candidates[candidate].eliminated)
            candidates[candidate].votes += 1;

        else
        {
            for (int remain_candidate = rank + 1; remain_candidate < candidate_count; remain_candidate++)
            {
                candidate = preferences[vote][remain_candidate];
                if (!candidates[candidate].eliminated)
                {
                    candidates[candidate].votes += 1;
                    break;
                }
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    bool is_winner = false;
    int majority;

    if (voter_count % 2)
        majority = round((float)voter_count/2);
    else
        majority = voter_count/2 + 1;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= majority)
        {
            is_winner = true;
            printf("%s\n", candidates[i].name);
            break;
        }
    }

    return is_winner;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int candidates_in_race = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
            candidates_in_race++;
    }


    int candidate_votes[candidates_in_race];
    int m = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
            candidate_votes[m++] = candidates[i].votes;
    }

    bubble_sort(candidate_votes, candidates_in_race);

    return candidate_votes[0];
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    bool is_tie = false;

    int eliminated_candidates = 0;
    int remaining_candidates = 0;
    int remaining[MAX_CANDIDATES];
    int m = 0, count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated)
            eliminated_candidates++;
        else
        {
            remaining_candidates++;
            remaining[m++] = i;
        }
    }

    for (int i = 0; i < remaining_candidates; i++)
    {
        int candidate = remaining[i];
        if (candidates[candidate].votes == min)
            count++;
    }

    if (count == remaining_candidates)
        is_tie = true;

    return is_tie;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
            candidates[i].eliminated = true;
    }
}

void bubble_sort(int arr[], int size)
{
    int i, j;
    for (i = 0; i < size - 1; i++)

        // Last i elements are already in place
        for (j = 0; j < size - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}