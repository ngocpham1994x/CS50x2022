//////////////////////>>>>>INCOMPLETE<<<<<///////////////////////
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair temps[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void print_preferences(int the_preferences[MAX][MAX]);
void swap(int* x, int* y);
void bubble_sort(int arr[], int size);
void print_array(int array[]);
void print_locked(bool the_locked[MAX][MAX]);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    print_preferences(preferences);
    print_locked(locked);

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return EXIT_SUCCESS;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    bool valid = true;
    int false_count = 0;

    // iterate over the candidate list
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
            ranks[rank] = i;
        else
            false_count++;
    }

    if (false_count == candidate_count)
        valid = false;

    return valid;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int rank_high = 0; rank_high < candidate_count; rank_high++)
    {
        int row = ranks[rank_high]; // number represents candidate

        for (int rank_low = rank_high + 1; rank_low < candidate_count; rank_low++)
        {
            int column = ranks[rank_low];

            preferences[row][column] += 1;
        }
    }
}

void print_preferences(int the_preferences[MAX][MAX])
{
    for (int row = 0; row < candidate_count; row++)
    {
        for (int column = 0; column < candidate_count; column++)
        {
            printf("%d ", the_preferences[row][column]);
        }
        printf("\n");
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;

    for (int each_candidate = 0; each_candidate < candidate_count; each_candidate++)
    {
        for (int other_candidate = each_candidate + 1; other_candidate < candidate_count; other_candidate++)
        {
            pair pair;
            if (preferences[each_candidate][other_candidate] > preferences[other_candidate][each_candidate])
            {
                pair.winner = each_candidate;
                pair.loser = other_candidate;
                pairs[pair_count++] = pair;
            }
            else if (preferences[each_candidate][other_candidate] < preferences[other_candidate][each_candidate])
            {
                pair.winner = other_candidate;
                pair.loser = each_candidate;
                pairs[pair_count++] = pair;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int array[pair_count];

    for (int i = 0; i < pair_count; i++)
        array[i] = preferences[pairs[i].winner][pairs[i].loser];

    print_array(array);

    bubble_sort(array, pair_count);

    print_array(array);


    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (array[i] == preferences[pairs[j].winner][pairs[j].loser])
            {
                temps[i] = pairs[j];
                pairs[j].winner = pairs[j].loser = 0;
                break;
            }
        }
    }

    for (int each_pair = 0; each_pair < pair_count; each_pair++)
        pairs[each_pair] = temps[each_pair];
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

void print_array(int array[])
{
    for (int i = 0; i < pair_count; i++)
        printf("%d ", array[i]);
    printf("\n");
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

void print_locked(bool the_locked[MAX][MAX])
{
    for (int row = 0; row < candidate_count; row++)
    {
        for (int column = 0; column < candidate_count; column++)
        {
            printf("%d ", the_locked[row][column]);
        }
        printf("\n");
    }
}

// Print the winner of the election
void print_winner(void)
{
    string winner;
    int count;

    for (int column = 0; column < candidate_count; column++)
    {
        // reset count
        count = 0;

        // for each row of the particular column
        for (int row = 0; row < candidate_count; row++)
        {
            // true = there is an edge from row to column
            if (locked[row][column])
                break;

            // false = there is no edge from row to column -> potentially a source of the graph
            else
                count++;
        }

        // if there are enough falses, meaning there are no edges pointing to the candidate -> it's the winner
        if (count == candidate_count)
        {
            printf("Winner: %s\n", candidates[column]);
            break;
        }
    }
}