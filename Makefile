.PHONY: all Common Engine Content TestApp

CONF = Debug

ARGS = CONF=$(CONF)

all: TestApp

run:
	cd Build/$(CONF)/; ./TestApp

clean:
	cd Common; make clean $(ARGS)
	cd Engine; make clean $(ARGS)
	cd Content; make clean $(ARGS)
	cd TestApp; make clean $(ARGS)

Common:
	cd Common; make $(ARGS)

Engine:
	cd Engine; make $(ARGS)

Content:
	cd Content; make $(ARGS)

TestApp:
	cd TestApp; make $(ARGS)
