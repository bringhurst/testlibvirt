all:
	gcc -g -Wall -o testlibvirt testlibvirt.c -lvirt

clean:
	+@rm -f ./testlibvirt
