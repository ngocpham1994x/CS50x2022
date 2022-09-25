# :file_folder: CS50x2022

> **ERROR 403 when `git push`**
>
> [Reminder msg on Discord](https://discord.com/channels/393846237255696385/395684800830373888/982680350784385144)

Error message:

```
remote: Permission to ....... denied to ......
fatal: unable to access '......git/': The requested URL returned error: 403
```

Solution:

```
git remote set-url <name> git@github.com:<username>/<repo>.git
git push
```

Example:
```
/workspaces/CS50x2022/ $ git remote set-url origin git@github.com:ngocpham1994x/CS50x2022.git
/workspaces/CS50x2022/ $ git push
```

# Intro


These are my own work for labs and assginments of CS50x2022 by Harvard College/OpenCourseWare.

In each week, there is a summary of knowledge that is worth to know and practice, as well as some extra shorts, videos or links I find helpful along the way to study for CS50.

Please note: **I DON'T USE CS50.h LIBRARY IN MY 2022 WORK**

Course materials:
- [This is CS50x](https://cs50.harvard.edu/x/2022/)
- [CS50's Manual](https://manual.cs50.io/#stdio.h)
- [CS50's All the docs](https://cs50.readthedocs.io/)
- [Discord discussion](https://discord.com/invite/cs50)
- [Reddit discussion](https://www.reddit.com/r/cs50/)

Enjoy and Happy coding! :robot:

# Timeline: :calendar:


- Week 0 Scratch
  - Find my Scratch game called Blue Balls [here](https://scratch.mit.edu/projects/471758222) :large_blue_circle:
  - Second version of Blue Balls [here](https://scratch.mit.edu/projects/471963172)
- Week 1 C
  - Knowledge sum-up:
  	- useful commands: `cd`,`cp`, `ls`, `mkdir`, `mv`, `rm`, `rmdir`, ...
  	- conditions: `if..else`
  	- loops: `for`, `do..while`, `while`
  	- format output `%i`, `%li`, `%c`
  	- limitations (32-bit, 64-bit), truncation
  	- abstraction (waterfall compiling), imprecision of 1/2, overflow, casting var type
  - Lab:
    - [hello.c](https://github.com/ngocpham1994x/CS50x2021/blob/main/pset1/hello/hello.c)
    - [population.c](https://github.com/ngocpham1994x/CS50x2021/blob/main/pset1/hello/population.c)
  - Problem Set 1:
    - [mario.c](https://github.com/ngocpham1994x/CS50x2021/blob/main/pset1/mario/mario.c) (mario-more)
    - [credit.c](https://github.com/ngocpham1994x/CS50x2021/blob/main/pset1/credit/credit.c)
    - [cash.c](https://github.com/ngocpham1994x/CS50x2021/blob/main/pset1/cash/cash.c)
- Week 2 Arrays
  - Lab: [scrabble.c](https://github.com/ngocpham1994x/CS50x2022/blob/main/pset2/scrabble/scrabble.c)
  - Problem Set 2:
    - [readability.c](https://github.com/ngocpham1994x/CS50x2022/blob/main/pset2/readability/readability.c)
    - [caesar.c](https://github.com/ngocpham1994x/CS50x2022/blob/main/pset2/caesar/caesar.c)
    - [substitution.c](https://github.com/ngocpham1994x/CS50x2022/blob/main/pset2/substitution/substitution.c)
- Week 3 Algorithms
  - Lab: [sort](/pset3/sort/answers.txt)
  - Problem Set 3:
    - [plurality.c](https://github.com/ngocpham1994x/CS50x2022/blob/main/pset3/plurality/plurality.c)
    - [runoff.c](https://github.com/ngocpham1994x/CS50x2022/blob/main/pset3/runoff/runoff.c)
    - [tideman.c](https://github.com/ngocpham1994x/CS50x2022/blob/main/pset3/tideman/tideman.c) - status: INCOMPLETE
- Week 4 Memory
  - Lab: [volume.c](/pset4/volume/volume.c)
  - Problem Set 4:
    - [filter.c](/pset4/filter-less/filter.c)
    - [recover.c](/pset4/recovery/recover.c)
- Week 5 Data Structures
  - Lab: [inheritance.c](/pset5/inheritance/inheritance.c)
  - Problem Set 5:
    - [speller.c](/pset6/speller/speller.c)
- Week 6 Python
  - Lab: worldcup - [tournament.py](/pset6/world-cup/tournament.py)
  - Problem Set 6:
    - [hello.py](/pset6/hello.py)
    - [mario.py](/pset6/mario.py)
    - [cash.py](/pset6/cash.py)
    - [readability.py](/pset6/readability.py)
    - [dna.py](/pset6/dna/dna.py)
- Week 7 SQL
  - Lab: [songs](/pset7/songs)
  - Problem Set 7:
    - [movies](/pset7/movies)
    - [fiftyville](/pset7/fiftyville/log.sql)

- Week 8 HTML, CSS, JavaScript
  - Lab: [trivia](/pset8/trivia/index.html)
  - Problem Set 8:
    - [homepage](/pset8/homepage)

- Week 9 Flask
  - Lab: [birthdays](/pset9/birthdays/)
  - Problem Set 9:
    - [finance](/pset9/finance)

- Week 10 Emoji
  - Final Project: [Gas Logger](/final-project)

- Extras:
  - Security

  - Artificial Intelligence
