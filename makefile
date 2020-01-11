CC = g++
SRCDIR = src
BUILDDIR = build
TARGET = bin/main.exe

SRCEXT = cpp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
CLFAGS = -g -Wall

clean: 
	rm -f $(BUILDDIR)/*.o
	rm -f $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CLFAGS) -c $< -o $@