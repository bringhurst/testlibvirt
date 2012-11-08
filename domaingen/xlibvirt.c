/*****************************************************************************\
 *  xlibvirt.c - libvirt related primitives
 *****************************************************************************
 *  Copyright (C) 2012 LANS
 *  Written by Jon Bringhurst <jonb@lanl.gov>
 *
 *  This file is part of SLURM, a resource management program.
 *  For details, see <http://www.schedmd.com/slurmdocs/>.
 *  Please also read the included file: DISCLAIMER.
 *
 *  SLURM is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  In addition, as a special exception, the copyright holders give permission
 *  to link the code of portions of this program with the OpenSSL library under
 *  certain conditions as described in each individual source file, and
 *  distribute linked combinations including the two. You must obey the GNU
 *  General Public License in all respects for all of the code used other than
 *  OpenSSL. If you modify file(s) with this exception, you may extend this
 *  exception to your version of the file(s), but you are not obligated to do
 *  so. If you do not wish to do so, delete this exception statement from your
 *  version.  If you delete this exception statement from all source files in
 *  the program, then also delete it here.
 *
 *  SLURM is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with SLURM; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA.
\*****************************************************************************/

#if HAVE_CONFIG_H
#   include "config.h"
#endif

#include "xlibvirt.h"

/*
 * Prototypes for internal functions
 */
xmlChar* _build_domain_xml(xlibvirt_domain_t* domain);
xmlNodePtr _build_domain_xml_os(xlibvirt_domain_os_t* os);
xmlNodePtr _build_domain_xml_devices(xlibvirt_domain_devices_t* devices);
xmlNodePtr _build_domain_xml_elements(xlibvirt_domain_elements_t* elements, char* type);

int
xlibvirt_boot_domain(xlibvirt_domain_t* domain) {
	/* TODO: Actually boot the domain. */
	fprintf(stdout, "%s\n", _build_domain_xml(domain));
	return -1;
}


/*****************************************************************************
 * Internal functions.
 *****************************************************************************/

/*
 * This will translate a domain struct into the xml schema required by
 * libvirt.
 */
xmlChar* _build_domain_xml(xlibvirt_domain_t* domain) {
        xmlDocPtr doc = NULL;
	xmlNodePtr elements_node = NULL;
        xmlChar *xml_buf;

        LIBXML_TEST_VERSION;
        doc = xmlNewDoc(BAD_CAST "1.0");

        elements_node = _build_domain_xml_elements(domain->opts, domain->type);

        xmlDocSetRootElement(doc, elements_node);
        xmlDocDumpFormatMemory(doc, &xml_buf, 0, 1);

        xmlFreeDoc(doc);
        xmlCleanupParser();

        return xml_buf;
}

xmlNodePtr
_build_domain_xml_os(xlibvirt_domain_os_t* os) {
	xmlNodePtr os_node = xmlNewNode(NULL, BAD_CAST "os");

	xmlNewChild(os_node, NULL, BAD_CAST "type", BAD_CAST os->type);
	xmlNewChild(os_node, NULL, BAD_CAST "init", BAD_CAST os->init);

	return os_node;
}

xmlNodePtr
_build_domain_xml_devices(xlibvirt_domain_devices_t* devices) {
	xmlNodePtr devices_node = xmlNewNode(NULL, BAD_CAST "devices");
	xmlNewChild(devices_node, NULL, BAD_CAST "emulator", BAD_CAST devices->emulator);

/*
	xlibvirt_domain_device_interface_t* curr = *interface;

	while(curr != NULL) {
		....
		curr++;
	}
*/
	return devices_node;
}

xmlNodePtr
_build_domain_xml_elements(xlibvirt_domain_elements_t* elements, char* type) {
	xmlNodePtr os_node = NULL;
	xmlNodePtr devices_node = NULL;
	xmlNodePtr elements_node = NULL;

	elements_node = xmlNewNode(NULL, BAD_CAST "domain");
        xmlNewProp(elements_node, BAD_CAST "type", BAD_CAST type);

	if(elements != NULL) {
		xmlNewChild(elements_node, NULL, BAD_CAST "name", BAD_CAST elements->name);
		xmlNewChild(elements_node, NULL, BAD_CAST "memory", elements->memory);
		xmlNewChild(elements_node, NULL, BAD_CAST "vcpu", elements->vcpu);
		xmlNewChild(elements_node, NULL, BAD_CAST "on_poweroff", BAD_CAST elements->on_poweroff);
		xmlNewChild(elements_node, NULL, BAD_CAST "on_reboot", BAD_CAST elements->on_reboot);
		xmlNewChild(elements_node, NULL, BAD_CAST "on_crash", BAD_CAST elements->on_crash);

		if(elements->os != NULL) {
			xmlAddChild(elements_node, _build_domain_xml_os(elements->os));
		}

		if(elements->devices != NULL) {
			xmlAddChild(elements_node, _build_domain_xml_devices(elements->devices));
		}
	}

	return elements_node;
}

/* EOF */
