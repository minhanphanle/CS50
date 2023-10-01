# TODO

from cs50 import get_int

height = get_int("Height: ")
while height > 8 or height <= 0:
    height = get_int("Height: ")


counter = height

# for i in range(height):
#     for k in range(counter-1):
#         print(" ", end="")
#     for n in range(height - counter + 1):
#         print("#", end="")
#     print("  ", end="")
#     for n in range(height - counter + 1):
#         print("#", end="")
#     for k in range(counter-1):
#         print(" ", end="")
#     print()
#     counter -= 1


# More efficient ver
for row in range(height):
    k = height - row - 1
    for column in range(height):
        if (column >= k):
            print("#", end="")
        else:
            print(" ", end="")
    print("  ", end="")
    for column in range(row + 1):
        print("#", end="")
    print()
