CC = g++
ENTRY_POINT = main.cpp
FLAGS = --std=c++17 -Wall
SDL = -F/Library/Frameworks -framework SDL2
VPATH = Classes:Headers
SRCS = main.cpp Player.cpp
OBJS = Player.o
HDRS = Vector2D.h Constants.h Player.h

game: $(OBJS) $(HDRS) $(SRCS)
	g++ $(ENTRY_POINT) -o game $(OBJS) $(FLAGS) $(SDL)

$(OBJS): %.o: %.cpp
	$(CC) -c $(FLAGS) $< -o $@

.PHONY: clean
clean:
	rm game *.o