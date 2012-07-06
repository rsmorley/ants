CC=g++
CFLAGS=-O3 -funroll-loops -c
LDFLAGS=-O2 -lm
HEADERS= AStar.h Bot.h Location.h Node.h State.h Bug.h Square.h Timer.h

SOURCES= AStar.cc Bot.cc MyBot.cc State.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=MyBot

#Uncomment the following to enable debugging
#CFLAGS+=-g -DDEBUG

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(HEADERS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o : %.cc $(HEADERS) 
	$(CC) $(CFLAGS) $< -o $@

clean: 
	-rm -f ${EXECUTABLE} ${OBJECTS} *.d
	-rm -f debug.txt

.PHONY: all clean
