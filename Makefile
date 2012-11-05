all:
	gcc -g -Wall -o testlibvirt testlibvirt.c -lvirt
	gcc -g -Wall -o getcaps getcaps.c -lvirt

clean:
	+@rm -f ./testlibvirt ./getcaps
