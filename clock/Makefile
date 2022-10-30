INCLUDE = $(INCLUDE_NOPI)
LDFLAGS = $(LDFLAGS_NOPI)

INCLUDE_NOPI := 
LDFLAGS_NOPI := -lncurses

all: clock

clock: display.o main.o
	cc -o $@ $^ $(LDFLAGS)

display.o: display.c display.h
	cc -o $@ -c $< $(INCLUDE)

main.o: main.c display.h
	cc -c $<

clean: 
	rm -f *.o clock

run:	
	./clock.sh | ./clock

