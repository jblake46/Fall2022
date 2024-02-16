default: driver.c functions.c functions.h poohWComment.ppm
	gcc -Wall driver.c functions.c -o driver.out

run: default
	./driver.out poohWComment.ppm poohWNoComment.ppm

clean:
	rm -vf *.out poohWNoComment.ppm 