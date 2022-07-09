import sys

while True:
    try:
        height = int(input("Height: "))
        if height > 0 and height < 9:
            break
    except ValueError:
        print("Input is not an integer")

for n in range(height):
    char = n + 1
    space = height - char
    print(" "*(space), end="")
    print("#"*(char))