CC = clang
CFLAGS = -static -O0
TARGET = laptop_breach
SOURCES = laptop_breach.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)
	strip $(TARGET)

clean:
	rm -f $(TARGET)
