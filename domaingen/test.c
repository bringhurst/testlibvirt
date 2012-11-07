#include <stdlib.h>
#include <stdio.h>

#include "xlibvirt.h"

xlibvirt_domain_t* build_domain() {
	return (xlibvirt_domain_t*)NULL;
}

int main(void) {
	char* xmlconfig;
	xlibvirt_domain_t* domain;

	domain = build_domain();
	xmlconfig = xlibvirt_create_domain_xml(domain);

	fprintf(stdout, "%s\n", xmlconfig);

	return 0;
}
