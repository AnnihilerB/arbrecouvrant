main: main.c 
	gcc -o main main.c

arbrecouvrant: arbrecouvrant.c 
	gcc -o arbrecouvrant arbrecouvrant.c

all: main arbrecouvrant

.PHONY : clean

clean:
	rm main arbrecouvrant	