#include <cs50.h>
#include <stdio.h>
#include <math.h>

int len(long number);
int first(long number);
int checksum(long number, long length);

int main(void)
{
    long number;
    number = get_long("Number: ");
    printf("%ld\n", number);

    long length;
    length = len(number);
    printf("%ld\n", length);

    long first_digit;
    first_digit = first(number);
    printf("%ld\n", first_digit);

    long checksum1;
    checksum1 = checksum(number, length);
    printf("%ld\n", checksum1);


    if ((length == 15) && ((first_digit == 34) || (first_digit == 37)) && (checksum1 == 1))
    {
        printf("AMEX\n");
    }
    else if ((length == 16) && ((first_digit == 51) || (first_digit == 52) || (first_digit == 53)|| (first_digit == 54)|| (first_digit == 55)) && (checksum1 == 1))
    {
        printf("MASTERCARD\n");
    }
    else if (((length == 16) || (length == 13)) && ((first_digit/10) == 4) && (checksum1 == 1))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

}

//length of card
int len(long number)
{
    int length=0;
    long n = number;
    while (n > 0)
    {
        n = n/10;
        length++;
    }
    return length;
}

//first digit of card
int first(long number)
{
    long k = number;
    while (k>=100)
    {
        k = k/10;
    }
    return k;
}

//Checksum - Luhn's algorithm

int checksum(long number, long length)
{
    int sum = 0;
    int n;
    long a = number;
    while (a >= 10)
    {
        n = 2*((a/10)%10);
        sum = sum + n%10 + n/10;
        a = a/100;
    }

    long h = number;
    int k;
    while (h > 0)
    {
        k = h%10;
        sum = sum + k;
        h = h/100;
    }

    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}
