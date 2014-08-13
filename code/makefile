CC=g++
CFLAGS=-c -g
LDFLAGS=-lavcodec -lavformat -lavutil -lswscale -lm
SOURCES = utils.cpp ViBE.cpp canny.cpp main.cpp dwt.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE = background.out
all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(EXECUTABLE1): $(OBJECTS1) 
	$(CC) $(OBJECTS1) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.out frame*.ppm bkframe*.ppm 
