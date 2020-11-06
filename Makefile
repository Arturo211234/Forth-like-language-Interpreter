CC = gcc
CFLAGS = -O2 -pipe -march=native -Wall -Wpedantic 
#Uncomment the next line and comment the one previous to this one to compile with debug symbols
#CFLAGS = -g -pipe -march=native -Wall -Wpedantic -Wextra

default:
	$(CC) $(CFLAGS) main.c -o forth
