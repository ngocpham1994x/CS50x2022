import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Missing command-line argument")
        sys.exit(1)

    # Read database file into a variable
    dna_counts = []
    sequence = ''
    subsequences = []

    db_filename = sys.argv[1]
    with open(db_filename) as db_file:
        database = csv.DictReader(db_file)

        for row in database:
            for key, value in row.items():
                if key != 'name':
                    row[key] = int(value)
                    subsequences.append(key)
            dna_counts.append(row)

    # for dna_count in dna_counts:
    #     print(f'{dna_count}')

    # Read DNA sequence file into a variable
    sq_filename = sys.argv[2]
    with open(sq_filename) as sq_file:
        sequence = sq_file.read()

    # print(f'\nsequence: {sequence}')

    # Find longest match of each STR in DNA sequence
    matches = {}
    for subsequence in subsequences:
        longest_run = longest_match(sequence, subsequence)
        matches[subsequence] = longest_run

    # print(f'\nmatches:\n {matches}')

    # Check database for matching profiles
    for i, dna_count in enumerate(dna_counts):
        # print(i, dna_count)
        count = 0
        for key, value in matches.items():
            if dna_count[key] == value:
                count += 1
            else:
                break
        if count == len(matches) and i < len(dna_counts):
            print(dna_count['name'])
            break
        elif count != len(matches) and i == len(dna_counts) - 1:
            print('No match')


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
