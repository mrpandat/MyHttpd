all:
	$(MAKE) -C src

clean:
	$(MAKE) -C src clean

doc:
	$(MAKE) -C src doc

test:
	$(MAKE) -C tests
