def get_cents():
    while True:
        try:
            cents = float(input("Change owed: "))
            if cents > 0:
                break
        except ValueError:
            pass

    return cents


def calculate_quarters(cents):
    quarters = 0

    while (cents >= 0.25):
        cents -= 0.25
        quarters += 1

    return quarters


def calculate_dimes(cents):
    dimes = 0

    while (cents >= 0.10):
        cents -= 0.10
        dimes += 1

    return dimes


def calculate_nickels(cents):
    nickels = 0

    while (cents >= 0.05):
        cents -= 0.05
        nickels += 1

    return nickels


def calculate_pennies(cents):
    pennies = 0

    while (cents >= 0.01):
        cents -= 0.01
        pennies += 1

    return pennies


def main():
    cents = get_cents()

    quarters = calculate_quarters(cents)
    cents = round(cents - quarters * 0.25, 2)

    dimes = calculate_dimes(cents)
    cents = round(cents - dimes * 0.10, 2)

    nickels = calculate_nickels(cents)
    cents = round(cents - nickels * 0.05, 2)

    pennies = calculate_pennies(cents)
    cents = round(cents - pennies * 0.01, 2)

    coins = quarters + dimes + nickels + pennies

    print(f"{coins}")


if __name__ == "__main__":
    main()