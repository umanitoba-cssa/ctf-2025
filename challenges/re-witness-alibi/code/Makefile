CC = clang
CFLAGS = -O0 -g
TARGET = witness_alibi
SOURCES = witness_alibi.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
