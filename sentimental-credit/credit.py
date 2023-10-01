
import re
from re import match
from cs50 import get_string


input = get_string("Number: ")


def main():
    number = int(input)
    luhnalgo = checksum(number)

    if bool(re.match('^3[47][0-9]{13}$', input)) and luhnalgo:
        print(f"AMEX")
    elif bool(re.match('^5[1-5][0-9]{14}$', input)) and luhnalgo:
        print(f"MASTERCARD")
    elif bool(re.match('^4[0-9]{12}(?:[0-9]{3})?$', input)) and luhnalgo:
        print(f"VISA")
    else:
        print("INVALID")


def checksum(number):
    a = number
    sum = 0
    while (a >= 10):

     # quotient when divide by 10 after having divided by 10
        n = 2 * ((a // 10) % 10)
        sum += n if n < 10 else n // 10 + n % 10
        a = a // 100

    b = number
    while (b > 0):
        sum += b % 10
        b = b // 100

    if sum % 10 == 0:
        return True
    else:
        return False


if __name__ == "__main__":
    main()

