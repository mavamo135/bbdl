CFLAGS= -ansi -Wall -c
all: project

project: ./main.o ./uart.o ./spi.o ./usrleds.o ./driver.o
	gcc -o project ./main.o ./uart.o ./spi.o ./usrleds.o ./driver.o

main.o: ./main.c
	gcc $(CFLAGS) ./main.c

uart.o: ./drivers/uart.c ./drivers/uart.h
	gcc $(CFLAGS) ./drivers/uart.c

spi.o: ./drivers/spi.c ./drivers/spi.h
	gcc $(CFLAGS) ./drivers/spi.c

usrleds.o: ./drivers/usrleds.c ./drivers/usrleds.h
	gcc $(CFLAGS) ./drivers/usrleds.c
	
driver.o: ./drivers/driver.c ./drivers/driver.h
	gcc $(CFLAGS) ./drivers/driver.c

clean:
	rm -f ./main.o ./uart.o ./spi.o ./usrleds.o ./driver.o
