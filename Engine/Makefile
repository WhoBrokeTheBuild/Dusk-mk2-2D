
CONF = Debug
ARGS = CONF=$(CONF)

CC = g++
AR = ar

CCFLAGS = -pedantic-errors -pedantic -std=c++14 -Wall
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
-I../Libraries/RapidXML/include/ \
`pkg-config --cflags lua` \
`pkg-config --cflags sfml-all`

SOURCES = \
Dusk/Audio/AudioSystem.cpp \
Dusk/Events/Callbacks.cpp \
Dusk/Events/Event.cpp \
Dusk/Events/EventDispatcher.cpp \
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
Dusk/Logging/Loggers/ConsoleLogger.cpp \
Dusk/Logging/Loggers/FileLogger.cpp \
Dusk/Logging/Logging.cpp \
Dusk/Scripting/ScriptHost.cpp \
Dusk/Scripting/Scripting.cpp \
Dusk/Tracking/TrackedObject.cpp \
Dusk/Tracking/MemoryTracker.cpp \
Dusk/UI/UIButton.cpp \
Dusk/UI/UIElement.cpp \
Dusk/UI/UIFont.cpp \
Dusk/UI/UIFrame.cpp \
Dusk/UI/UIInput.cpp \
Dusk/UI/UILabel.cpp \
Dusk/UI/UIManager.cpp \
Dusk/Utility/Strings.cpp \
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
