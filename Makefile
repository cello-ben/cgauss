SRC_DIR = src
INC = src/include
CFLAGS = -Wall -Wpedantic -Wextra  -Wno-unused-parameter -Wno-unused-function -Werror -std=gnu99

all:
	gcc -o cgauss $(SRC_DIR)/*.c -I$(INC) $(CFLAGS) -O3

debug:
	gcc -g -o cgauss $(SRC_DIR)/*.c -I$(INC) $(CFLAGS)

clean:
	rm -rf cgauss *.o *.dSYM