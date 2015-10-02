WORKDIR = `pwd`

CONF = Debug
ARGS = CONF=$(CONF)

CC = g++
LD = g++

CCFLAGS = -pedantic-errors -pedantic -std=c++11 -Wall
LDFLAGS =

ifeq ($(CONF), Debug)
    CCFLAGS += -g -DDEBUG
endif
ifeq ($(CONF), Release)
    CCFLAGS += -O2 -DRELEASE
endif

OBJDIR = Build/$(CONF)
OUTDIR = ../Build/$(CONF)
OUT = $(OUTDIR)/TestApp

INC_PATH = \
-I../Engine/ \
`pkg-config --cflags lua5.2` \
`pkg-config --cflags sfml-all`

LIB_PATH = \
-L$(OUTDIR)

LIBS = \
-ldusk-engine \
`pkg-config --libs lua5.2` \
`pkg-config --libs sfml-all`

SOURCES = \
TestApp.cpp \
Main.cpp

OBJECTS=$(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

all: deps $(OUT)

deps:
	cd ../Engine; make $(ARGS)

clean:
	rm -f $(OUT)
	rm -rf $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	mkdir -p `dirname $@`
	$(CC) $(CCFLAGS) $(INC_PATH) -c $< -o $@

$(OUT): $(OBJECTS)
	mkdir -p $(OUTDIR)
	$(LD) $(LDFLAGS) $(LIB_PATH) $(OBJECTS) $(LIBS)-o $(OUT)
