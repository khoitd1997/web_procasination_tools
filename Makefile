all:
	gcc main.c -Wall -lpcap -o web_procasination.out

clean:
	rm -f *.out