default: driver.c ppm.h ppm.c EncodeDecode.h EncodeDecode.c
	gcc -Wall driver.c ppm.c EncodeDecode.c -o driver.out

run: default
	./driver.out input.ppm output.ppm

clean:
	@rm -vf *.out out*