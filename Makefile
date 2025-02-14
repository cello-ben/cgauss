SRC_DIR = src
INC = src/include
CFLAGS = -Wall -Wpedantic -Wextra  -Wno-unused-parameter -Wno-unused-function -Werror -std=gnu99

all:
	gcc -o gaussian $(SRC_DIR)/*.c -I$(INC) $(CFLAGS) -O3

debug:
	gcc -g -o gaussian $(SRC_DIR)/*.c -I$(INC) $(CFLAGS)

clean:
	rm -rf gaussian *.o *.dSYM