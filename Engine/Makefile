WORKDIR = `pwd`

CONF = 'Debug'
ARCH = x64

CC = g++
AR = ar

CCFLAGS = -pedantic-errors -pedantic -std=c++11 -Wall
ARFLAGS = rvs

ifeq $(CONF) 'Debug'
    CCFLAGS = $(CCFLAGS) -g -DDEBUG
endif
ifeq $(CONF) 'Release'
    CCFLAGS = $(CCFLAGS) -O2 -DRELEASE
endif

OBJDIR = Build/$(CONF)/$(ARCH)
OUTDIR = ../Build/$(CONF)/$(ARCH)
OUT = $(OUTDIR)/dusk-engine.a

INC = \
-I. \
-I../Common
-I../Libraries/lua/include \
-I../Libraries/SFML/include

SOURCES = \
Dusk/Graphics/GraphicsContext.cpp \
Dusk/Graphics/GraphicsSystem.cpp \
Dusk/Graphics/Sprite.cpp \
Dusk/Graphics/Texture.cpp \
Dusk/Input/Inputs/Key.cpp \
Dusk/Input/Inputs/Mouse.cpp \
Dusk/Input/Inputs/Mapped.cpp \
Dusk/Input/InputSystem.cpp \
Dusk/UpdateEventData.cpp \
Dusk/RenderEventData.cpp \
Dusk/Program.cpp

OBJECTS=$(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

all: $(OUT)

clean:
	rm -f $(OUT)
	rm -rf $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	mkdir -p `dirname $@`
	$(CC) $(CCFLAGS) $(INC) -c $< -o $@

$(OUT): $(OBJECTS)
	$(AR) $(ARFLAGS) $(OUT) $(OBJECTS)
