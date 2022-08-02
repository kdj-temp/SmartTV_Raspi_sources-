CC=g++
CFLAGS=-I.

loopplayermake: base64.o Rijndael.o cryption.o file-op.o jsoncpp.o command-sender.o logic.o main.o 
	$(CC) -o loopplayer base64.o Rijndael.o cryption.o file-op.o jsoncpp.o command-sender.o logic.o  main.o -I.
