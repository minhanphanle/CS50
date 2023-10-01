import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    people = []
    str_list = []
    # Read database file into a variable
    with open(sys.argv[1]) as file:
        reader = csv.reader(file)
        for row in reader:
            str_list = row
            str_list.pop(0)
            break

    with open(sys.argv[1]) as file:
        dict_reader = csv.DictReader(file)
        for row in dict_reader:
            people.append(row)

    # Read DNA sequence file into a variable

    dna_string = ""
    with open(sys.argv[2]) as file:
        dna_string += file.read()

    # print(people)
    # print(str_list)
    # print(dna_string)
    result_dict = {}
    # Find longest match of each STR in DNA sequence
    for i in str_list:
        result_dict[i] = str(longest_match(dna_string, i))

    # print(result_dict)

    # Check database for matching profiles
    for person in people:
        count = 0
        for key in result_dict.keys():
            if result_dict[key] != person[key]:
                break
            count += 1
        if count == len(result_dict.keys()):
            print(person['name'])
            return
    print("No match")


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
