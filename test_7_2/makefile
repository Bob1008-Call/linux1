CC = g++
CFLAGS = -std=c++11 -ljsoncpp

all: Deserialize.cpp Serialize.cpp 
	$(CC) $(CFLAGS) Serialize.cpp  -o Serialize
	$(CC) $(CFLAGS) Deserialize.cpp -o Deserialize 

clean:
	rm Deserialize Serialize
