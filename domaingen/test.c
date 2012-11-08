/*
 * Populate slurm libvirt structures with test data and produce output
 * necessary for libvirtd to launch the domain.
 */

#include <stdlib.h>
#include <stdio.h>

#include "xlibvirt.h"


/* prototypes */
xlibvirt_domain_os_t* build_domain_os();
xlibvirt_domain_devices_t* build_domain_devices();
xlibvirt_domain_device_console_t* build_domain_device_console();
xlibvirt_domain_device_filesystem_t* build_domain_device_filesystem();
xlibvirt_domain_device_filesystem_source_t* build_domain_device_filesystem_source();
xlibvirt_domain_device_filesystem_target_t* build_domain_device_filesystem_target();
xlibvirt_domain_device_interface_t* build_domain_device_interface();
xlibvirt_domain_device_interface_source_t* build_domain_device_interface_source();
xlibvirt_domain_elements_t* build_domain_elements();
xlibvirt_domain_t* build_domain();


xlibvirt_domain_os_t* build_domain_os() {
	/*
	<os>
		<type>exe</type>
		<init>/bin/bash</init>
	</os>
	*/

	xlibvirt_domain_os_t* os = (xlibvirt_domain_os_t*) malloc(sizeof(xlibvirt_domain_os_t));

	os->type = "exe";
	os->init = "/bin/bash";

	return os;
}

xlibvirt_domain_devices_t* build_domain_devices() {
	/*
	<devices>
		<emulator>/usr/lib/libvirt/libvirt_lxc</emulator>
		...
	</devices>
	*/

	xlibvirt_domain_devices_t* devices =
		(xlibvirt_domain_devices_t*) malloc(sizeof(xlibvirt_domain_devices_t));

	devices->interfaces = (xlibvirt_domain_device_interface_t**) malloc(sizeof(xlibvirt_domain_device_interface_t*) * 2);
	devices->filesystems = (xlibvirt_domain_device_filesystem_t**) malloc(sizeof(xlibvirt_domain_device_console_t*) * 2);
	devices->consoles = (xlibvirt_domain_device_console_t**) malloc(sizeof(xlibvirt_domain_device_console_t*) * 2);

	devices->interfaces[0] = build_domain_device_interface();
	devices->filesystems[0] = build_domain_device_filesystem();
	devices->consoles[0] = build_domain_device_console();

	devices->interfaces[1] = NULL;
	devices->filesystems[1] = NULL;
	devices->consoles[1] = NULL;

	devices->pools = NULL;

	return devices;
}

xlibvirt_domain_device_console_t* build_domain_device_console() {
        /*
	<console type='pty' />
        */

	xlibvirt_domain_device_console_t* console =
		(xlibvirt_domain_device_console_t*) malloc(sizeof(xlibvirt_domain_device_console_t));

	console->type = "pty";

        return console;
}

xlibvirt_domain_device_filesystem_t* build_domain_device_filesystem() {
        /*
	<filesystem type='mount'>
	...
	</filesystem>
        */

	xlibvirt_domain_device_filesystem_t* filesystem =
		(xlibvirt_domain_device_filesystem_t*) malloc(sizeof(xlibvirt_domain_device_filesystem_t));

	filesystem->type = "mount";

	filesystem->source = build_domain_device_filesystem_source();
	filesystem->target = build_domain_device_filesystem_target();

        return filesystem;
}

xlibvirt_domain_device_filesystem_source_t* build_domain_device_filesystem_source() {
        /*
	<source dir='/'/>
        */

	xlibvirt_domain_device_filesystem_source_t* source =
		(xlibvirt_domain_device_filesystem_source_t*) malloc(sizeof(xlibvirt_domain_device_filesystem_source_t));

	source->dir = "/";

        return source;
}

xlibvirt_domain_device_filesystem_target_t* build_domain_device_filesystem_target() {
        /*
	<target dir='/'/>
        */

	xlibvirt_domain_device_filesystem_target_t* target =
		(xlibvirt_domain_device_filesystem_target_t*) malloc(sizeof(xlibvirt_domain_device_filesystem_target_t));

	target->dir = "/";

        return target;
}

xlibvirt_domain_device_interface_t* build_domain_device_interface() {
	/*
	<interface type='network'>
	...
	</interface>
	*/

	xlibvirt_domain_device_interface_t* interface =
		(xlibvirt_domain_device_interface_t*) malloc(sizeof(xlibvirt_domain_device_interface_t));

	interface->type = "network";

	interface->sources = (xlibvirt_domain_device_interface_source_t**) malloc(sizeof(xlibvirt_domain_device_interface_source_t*) * 2);

	interface->sources[0] = build_domain_device_interface_source();
	interface->sources[1] = NULL;

	return interface;
}

xlibvirt_domain_device_interface_source_t* build_domain_device_interface_source() {
	/*
	<source network='default'/>
	*/

	xlibvirt_domain_device_interface_source_t* source =
		(xlibvirt_domain_device_interface_source_t*) malloc(sizeof(xlibvirt_domain_device_interface_source_t));

	return source;
}

xlibvirt_domain_elements_t* build_domain_elements() {
	/*
	<name>vm1</name>
	<memory>30000</memory>
	<vcpu>1</vcpu>
	<clock offset='utc'/>
	<on_poweroff>destroy</on_poweroff>
	<on_reboot>restart</on_reboot>
	<on_crash>destroy</on_crash>
	...
	*/

	xlibvirt_domain_elements_t* elements =
		(xlibvirt_domain_elements_t*) malloc(sizeof(xlibvirt_domain_elements_t));

	elements->name = "domaingen_test_domain";
	elements->clock_offset = "utc";

	elements->memory = "30000";
	elements->vcpu = "1";

        elements->on_poweroff = "destroy";
        elements->on_reboot = "restart";
        elements->on_crash = "destroy";

	elements->os = build_domain_os();
	elements->devices = build_domain_devices();

	return elements;
}

xlibvirt_domain_t* build_domain() {
	/*
	<domain type='lxc'>
	...
	</domain>
	*/

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

/* EOF */
