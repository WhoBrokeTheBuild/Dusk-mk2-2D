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
OUT = $(OUTDIR)/dusk-common.a

INC = \
-I. \
-I../Libraries/lua/include \
-I../Libraries/SFML/include

SOURCES = \
Dusk/Events/Callbacks.cpp \
Dusk/Events/Event.cpp \
Dusk/Events/IEventDispatcher.cpp \
Dusk/Logging/LoggingSystem.cpp \
Dusk/Logging/Logger.cpp \
Dusk/Logging/Loggers/ConsoleLogger.cpp \
Dusk/Logging/Loggers/FileLogger.cpp \
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
	$(CC) $(CCFLAGS) $(INC) -c $< -o $@

$(OUT): $(OBJECTS)
	$(AR) $(ARFLAGS) $(OUT) $(OBJECTS)
