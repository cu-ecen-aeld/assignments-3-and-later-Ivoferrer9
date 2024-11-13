cc = gcc
CROSS_COMPILE ?=
CFLAGS = -Wall -Werror

TARGET = writer

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
clean:
	rm -f $(TARGET)
