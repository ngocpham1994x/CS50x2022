#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void mergeSort(int arr[], int start, int end);
void merge(int arr[], int start, int mid, int end);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
            printf("%i vote(s) remained.\n", voter_count - 1 - i);
        }
        else
        {
            printf("Valid vote.\n");
            printf("%i vote(s) remained.\n", voter_count - 1 - i);
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int votes_arr[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        votes_arr[i] = candidates[i].votes;
    }

    //merge sort, ascending
    mergeSort(votes_arr, 0, candidate_count - 1);


    //print name(s) of winner(s)
    int highest_vote = votes_arr[candidate_count - 1];
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == highest_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}




// Merges two subarrays of arr[].
// First subarray is arr[start..mid]
// Second subarray is arr[mid+1..end]
void merge(int arr[], int start, int mid, int end)
{
    int i, j, k;
    int n1 = mid - start + 1;
    int n2 = end - mid;

    // create temp arrays
    int left[n1], right[n2];

    // Copy data to temp arrays left[] and right[]
    for (i = 0; i < n1; i++)
    {
        left[i] = arr[start + i];
    }
    for (j = 0; j < n2; j++)
    {
        right[j] = arr[mid + 1 + j];
    }

    // Merge the temp arrays back into arr[star..end]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = start; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of left[], if there are any
    while (i < n1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    // Copy the remaining elements of right[], if there are any
    while (j < n2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}


void mergeSort(int arr[], int start, int end)
{
    if (start < end)
    {
        // Same as (start + end)/2, but avoids overflow for large start and end
        int mid = start + (end - start) / 2;

        // Sort first and second halves
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);

        merge(arr, start, mid, end);
    }
}
