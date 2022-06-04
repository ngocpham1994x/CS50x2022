# :file_folder: CS50x2022

**ERROR 403 when `git push`**

[Reminder msg on Discord](https://discord.com/channels/393846237255696385/395684800830373888/982680350784385144)

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
  - Lab: [sort]()
  - Problem Set 2:
    - [plurality.c](https://github.com/ngocpham1994x/CS50x2022/blob/main/pset3/plurality/plurality.c)
    - [runoff.c](https://github.com/ngocpham1994x/CS50x2022/blob/main/pset3/runoff/runoff.c)
    - [tideman.c](https://github.com/ngocpham1994x/CS50x2022/blob/main/pset3/tideman/tideman.c) - status: INCOMPLETE
- Week 4 Memory

- Week 5 Data Structures

- Week 6 Python

- Week 7 SQL

- Week 8 HTML, CSS, JavaScript

- Week 9 Flask

- Week 10 Ethics

- Extras:
  - Security

  - Artificial Intelligence

- Final Project
