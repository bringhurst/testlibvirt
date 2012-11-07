#include <stdlib.h>
#include <stdio.h>

#include "xlibvirt.h"

xlibvirt_domain_elements_t* build_domain_elements() {
	return (xlibvirt_domain_elements_t*) NULL;
}

xlibvirt_domain_t* build_domain() {
	xlibvirt_domain_t* domain =
		(xlibvirt_domain_t*) malloc(sizeof(xlibvirt_domain_t));

	domain->type = "lxc";
	domain->opts = build_domain_elements();

	return domain;
}

int main(void) {
	char* xmlconfig;
	xlibvirt_domain_t* domain;

	xmlconfig = xlibvirt_build_domain_xml(build_domain());
	fprintf(stdout, "%s\n", xmlconfig);

	return 0;
}
