.PHONY: all Common Engine Content TestApp

CONF = Debug

ARGS = CONF=$(CONF)

all: TestApp

run:
	cd TestApp; export LUA_PATH="../ScriptLib/?.lua;"; ../Build/$(CONF)/TestApp

clean:
	cd Engine; make clean $(ARGS)
	cd TestApp; make clean $(ARGS)

Engine:
	cd Engine; make $(ARGS)

TestApp:
	cd TestApp; make $(ARGS)
