all:HW3

HW3 : HW3.o arrays.o Spacial.o Circles.o
	gcc -o HW3 HW3.o arrays.o Spacial.o Circles.o
	
Spacial.o : Spacial.c Spacial.h arrays.h
	gcc -std=c99 Spacial.c -lm
	
arrays.o : arrays.c arrays.h
	gcc -std=c99  arrays.c -lm
	
Circles.o : Circles.c Circles.h
	gcc -std=c99  Circles.c -lm
	
HW3.o : HW3.c arrays.h Spacial.h Circles.h
	gcc -std=c99 HW3.c arrays.c Spacial.c Circles.h -lm
	
clean : 
	rm HW3.o arrays.o Spacial.o Circles.o
