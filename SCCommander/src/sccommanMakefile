CC=g++
CFLAGS=-I.

sccommandermake: base64.o Rijndael.o cryption.o data-getter.o file-op.o jsoncpp.o command-sender.o s-connector.o core.o main.o 
	$(CC) -o sccomman base64.o Rijndael.o cryption.o data-getter.o file-op.o jsoncpp.o command-sender.o s-connector.o core.o  main.o -lcurl -I.
