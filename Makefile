all:
	$(MAKE) -C src

clean:
	$(MAKE) -C src clean

doc:
	$(MAKE) -C src doc

check:
	$(MAKE) -C tests check
