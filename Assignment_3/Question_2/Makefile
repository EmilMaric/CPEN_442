CC := gcc -O3
LIBS := -lm -lssl -lcrypto

all: sha_test

sha_test: sha_test.c
	${CC} ${LIBS} $< -o $@

clean:
	rm sha_test
