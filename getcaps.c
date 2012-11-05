#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

int main(int argc, char *argv[])
{
	virConnectPtr conn;
	char *caps;

	conn = virConnectOpen("lxc+unix://");
	if (conn == NULL) {
		fprintf(stderr, "Failed to open connection to lxc+unix://\n");
		return 1;
	}

	caps = virConnectGetCapabilities(conn);
	fprintf(stdout, "Capabilities:\n%s\n", caps);
	free(caps);

	virConnectClose(conn);
	return 0;
}
