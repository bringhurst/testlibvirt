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
void _build_domain_xml_os(xlibvirt_domain_os_t* os, xmlNodePtr root_node);
void _build_domain_xml_devices(xlibvirt_domain_devices_t* devices, xmlNodePtr root_node);
void _build_domain_xml_elements(xlibvirt_domain_elements_t* elements, xmlNodePtr root_node);

/*
 * This will translate a domain struct into the xml schema required by
 * libvirt.
 */
xmlChar* xlibvirt_build_domain_xml(xlibvirt_domain_t* domain) {
	xmlDocPtr doc = NULL;
	xmlNodePtr root_node = NULL;
	xmlChar *xml_buf;

	LIBXML_TEST_VERSION;
	doc = xmlNewDoc(BAD_CAST "1.0");

	root_node = xmlNewNode(NULL, BAD_CAST "domain");
	xmlNewProp(root_node, BAD_CAST "type", BAD_CAST domain->type);

	_build_domain_xml_elements(domain->opts, root_node);

	xmlDocSetRootElement(doc, root_node);
	xmlDocDumpFormatMemory(doc, &xml_buf, 0, 1);

	xmlFreeDoc(doc);
	xmlCleanupParser();

	return xml_buf;
}

int
xlibvirt_boot_domain(xlibvirt_domain_t domain) {
	return -1;
}


/*****************************************************************************
 * Internal functions.
 *****************************************************************************/

void
_build_domain_xml_os(xlibvirt_domain_os_t* os, xmlNodePtr root_node) {

}

void
_build_domain_xml_devices(xlibvirt_domain_devices_t* devices, xmlNodePtr root_node) {

}

void
_build_domain_xml_elements(xlibvirt_domain_elements_t* elements, xmlNodePtr root_node) {
	xmlNodePtr os_node = xmlNewNode(NULL, BAD_CAST "os");
	xmlNodePtr devices_node = xmlNewNode(NULL, BAD_CAST "devices");

	xmlNewChild(root_node, NULL, BAD_CAST "name", BAD_CAST elements->name);
	xmlNewChild(root_node, NULL, BAD_CAST "memory", BAD_CAST elements->memory);
	xmlNewChild(root_node, NULL, BAD_CAST "vcpu", BAD_CAST elements->vcpu);
	xmlNewChild(root_node, NULL, BAD_CAST "on_poweroff", BAD_CAST elements->on_poweroff);
	xmlNewChild(root_node, NULL, BAD_CAST "on_reboot", BAD_CAST elements->on_reboot);
	xmlNewChild(root_node, NULL, BAD_CAST "on_crash", BAD_CAST elements->on_crash);

	_build_domain_xml_os(elements->os, os_node);
	_build_domain_xml_devices(elements->devices, devices_node);

	xmlAddChild(root_node, os_node);
	xmlAddChild(root_node, devices_node);
}
