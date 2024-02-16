default: driver.c functions.c functions.h poohWComment.ppm
	gcc -Wall driver.c functions.c -o driver.out

run: default
	./driver.out input.ppm negative.ppm resize.ppm

clean:
	rm -vf *.out 