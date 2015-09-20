
CONF = Debug
ARGS = CONF=$(CONF)

CC = g++
AR = ar

CCFLAGS = -pedantic-errors -pedantic -std=c++11 -Wall
ARFLAGS = rvs

ifeq ($(CONF), Debug)
    CCFLAGS += -g -DDEBUG
endif
ifeq ($(CONF), Release)
    CCFLAGS += -O2 -DRELEASE
endif

OBJDIR = Build/$(CONF)
OUTDIR = ../Build/$(CONF)
OUT = $(OUTDIR)/libdusk-common.a

INC_PATH = \
-I. \
`pkg-config --cflags lua5.2`

SOURCES = \
Dusk/Events/Callbacks.cpp \
Dusk/Events/Event.cpp \
Dusk/Events/IEventDispatcher.cpp \
Dusk/Logging/Loggers/ConsoleLogger.cpp \
Dusk/Logging/Loggers/FileLogger.cpp \
Dusk/Logging/Logging.cpp \
Dusk/Scripting/ScriptHost.cpp \
Dusk/Scripting/Scripting.cpp \
Dusk/Tracking/ITrackedObject.cpp \
Dusk/Tracking/MemoryTracker.cpp \
Dusk/Utility/Strings.cpp

OBJECTS=$(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

all: $(OUT)

clean:
	rm -f $(OUT)
	rm -rf $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	mkdir -p `dirname $@`
	$(CC) $(CCFLAGS) $(INC_PATH) -c $< -o $@

$(OUT): $(OBJECTS)
	mkdir -p $(OUTDIR)
	$(AR) $(ARFLAGS) $(OUT) $(OBJECTS)
