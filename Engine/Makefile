
CONF = Debug
ARGS = CONF=$(CONF)

CC = g++
AR = ar

CCFLAGS = -pedantic-errors -pedantic -std=c++11 -Wall
ARFLAGS = rvs

ifeq ($(CONF), 'Debug')
    CCFLAGS += -g -DDEBUG
endif
ifeq ($(CONF), 'Release')
    CCFLAGS += -O2 -DRELEASE
endif

OBJDIR = Build/$(CONF)
OUTDIR = ../Build/$(CONF)
OUT = $(OUTDIR)/libdusk-engine.a

INC_PATH = \
-I. \
`pkg-config --cflags lua5.2` \
`pkg-config --cflags sfml-all`

SOURCES = \
Dusk/Graphics/GraphicsContext.cpp \
Dusk/Graphics/GraphicsSystem.cpp \
Dusk/Graphics/Sprite.cpp \
Dusk/Graphics/Texture.cpp \
Dusk/Graphics/Font.cpp \
Dusk/Graphics/TextBuffer.cpp \
Dusk/Input/InputSystem.cpp \
Dusk/Input/Keyboard.cpp \
Dusk/Input/Mouse.cpp \
Dusk/Input/Mapped.cpp \
Dusk/UpdateEventData.cpp \
Dusk/RenderEventData.cpp \
Dusk/Program.cpp

OBJECTS=$(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

all: deps $(OUT)

deps:

clean:
	rm -f $(OUT)
	rm -rf $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	mkdir -p `dirname $@`
	$(CC) $(CCFLAGS) $(INC_PATH) -c $< -o $@

$(OUT): $(OBJECTS)
	mkdir -p $(OUTDIR)
	$(AR) $(ARFLAGS) $(OUT) $(OBJECTS)
