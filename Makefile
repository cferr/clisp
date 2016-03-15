.PHONY=all clean
OBJECTS=parser.o env.o common.o clisp.o
EXECUTABLE=clisp
LDFLAGS=
CCFLAGS= -std=c99
LIBS=

all: $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	gcc $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)

%.o:%.c
	gcc -o $@ $(@:.o=.c) $(CFLAGS) -c

clean:
	rm -f *.o $(EXECUTABLE)
