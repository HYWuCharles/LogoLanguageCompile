LIBS = `sdl2-config --libs` -lm
CFLAGS = `sdl2-config --cflags` -Wall -Wextra -Werror -Wfloat-equal -pedantic -ansi $(LIBS)
TESTFLAGS = -Wall -Wextra -Werror -Wfloat-equal -pedantic -ansi -lm
DEBUG = -g3
OPTIM = -O2
VALGRIND = --error-exitcode=1 --quiet --leak-check=full

all: compile dictTest stackTest stackTestFloat

compile: compile.c parser.c dict.c FloatStack.c Stack.c SDLutil.c
		$(CC) compile.c parser.c dict.c FloatStack.c Stack.c SDLutil.c -o compile $(CFLAGS) $(OPTIM)

extension: compile_extension.c parser_extension.c dict.c FloatStack.c Stack.c SDLutil.c
		$(CC) compile_extension.c parser_extension.c dict.c FloatStack.c Stack.c SDLutil.c -o compile $(CFLAGS) $(OPTIM)

run: compile
		./compile example.txt

dictTest: dictTest.c dict.c
		$(CC) dictTest.c dict.c -o dictTest $(TESTFLAGS) $(OPTIM)

stackTest: StackTest.c Stack.c
		$(CC) StackTest.c Stack.c -o stackTest $(TESTFLAGS) $(OPTIM)

stackTestFloat: FloatStackTest.c FloatStack.c
		$(CC) FloatStackTest.c FloatStack.c -o stackTestFloat $(TESTFLAGS) $(OPTIM)

clean:
		rm -f compile dictTest stackTest stackTestFloat
