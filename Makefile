.PHONY: all Common Engine Content TestApp

CONF = Debug

ARGS = CONF=$(CONF)

all: TestApp

run:
	cd Build/$(CONF)/; ./TestApp

clean:
	cd Engine; make clean $(ARGS)
	cd TestApp; make clean $(ARGS)

Engine:
	cd Engine; make $(ARGS)

TestApp:
	cd TestApp; make $(ARGS)
