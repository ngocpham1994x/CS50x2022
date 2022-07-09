
MAX_LENGTH = 1000
CONST1 = 0.0588
CONST2 = 0.296
CONST3 = 15.8


def count_letters(text):
    letters = 0

    for i in range(len(text)):
        if((text[i] >= 'a' and text[i] <= 'z') or (text[i] >= 'A' and text[i] <= 'Z')):
            letters += 1

    return letters


def count_words(text):
    words = 0

    for i in range(len(text)):
        if(text[i] == ' '):
            words += 1

    return words + 1


def count_sentences(text):
    sentences = 0

    for i in range(len(text)):
        if(text[i] == '.' or text[i] == '?' or text[i] == '!'):
            sentences += 1

    return sentences


def main():
    text = input("Text: ")

    words = count_words(text)
    sentences = count_sentences(text)
    letters = count_letters(text)

    L = letters / words * 100
    S = sentences / words * 100

    index = round(CONST1 * L - CONST2 * S - CONST3)

    print(f"{letters} letter(s)")
    print(f"{sentences} sentence(s)")
    print(f"{words} word(s)")

    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()