all: build install

build: *.cpp *.h templatelib/*.py
	python3 setup.py config build_ext --inplace

.PHONY: clean install check

install:
	python3 setup.py install

clean:
	rm -rf build dist *.egg-info templatelib/*.so

check:
	$(MAKE) check --print-directory -C templatelib
