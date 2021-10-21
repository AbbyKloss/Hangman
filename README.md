# Hangman v1.0

Initially exported as a simple terminal game for me and my friends to maybe play. The following is largely unmodified from the readme I wrote for it in early 2021.

### IMPORTANT:
You must have words_alpha.txt in the same directory as hangman.o and you must have some
Linux terminal to execute hangman.o in.

### Less important:
Some sample execution is
  "./hangman.o 3"
to have 3 lives. Another way to express this is that the first and only argument is the
amount of lives you have in this silly hangman game. The default number of lives is 6.

### Planned:
Some form of save file, it would be argument 2. I just don't feel like implementing it
right now, but what you would expect to see is a txt file full of words that you've
already used output to the text file you specified in argv[2].
