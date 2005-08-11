/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <errno.h>
#include <netinet/in.h>

#include <bluetooth/sdp.h>
#include <bluetooth/sdp_lib.h>


struct search_context {
	char 		*svc;		/* Service */
	uuid_t		group;		/* Browse group */
	int		tree;		/* Display full attribute tree */
	uint32_t	handle;		/* Service record handle */
};


int estr2ba(char *str, bdaddr_t *ba)
{
	/* Only trap "local", "any" is already dealt with */
	if(!strcmp(str, "local")) {
		bacpy(ba, BDADDR_LOCAL);
		return 0;
	}
	return str2ba(str, ba);
}

void sdp_printf_service_attr(sdp_record_t *rec)
{
	if (rec && rec->attrlist) {
		struct service_context service = { NULL };
		sdp_list_foreach(rec->attrlist, sdp_attr_printf_func, &service);
	}
}


int main(int argc, char **argv)
{
	struct search_context context;
	static bdaddr_t bdaddr;
	static bdaddr_t interface;
	
	/* Initialise context */
	memset(&context, '\0', sizeof(struct search_context));
	/* We want to browse the top-level/root */
	sdp_uuid16_create(&(context.group), PUBLIC_BROWSE_GROUP);
	
	if (argc >= 1) {
		estr2ba(argv[1], &bdaddr);
	}else{
		printf("Usage : %s  <baddr>\n", argv[0]);
		exit(1);
	}
	
	sdp_list_t *attrid, *search, *seq, *next;
	uint32_t range = 0x0000ffff;
	char str[20];
	sdp_session_t *sess;
	
	sess = sdp_connect(BDADDR_ANY, &bdaddr, SDP_RETRY_IF_BUSY);
	ba2str(&bdaddr, str);
	if (!sess) {
		printf("Failed to connect to SDP server on %s: %s\n", str, strerror(errno));
		return -1;
	}
	if (context.svc)
		printf("Searching for %s on %s ...\n", context.svc, str);
	else
		printf("Browsing %s ...\n", str);

	attrid = sdp_list_append(0, &range);
	search = sdp_list_append(0, &context.group);
	if (sdp_service_search_attr_req(sess, search, SDP_ATTR_REQ_RANGE, attrid, &seq)) {
		printf("Service Search failed: %s\n", strerror(errno));
		sdp_close(sess);
		return -1;
	}
	sdp_list_free(attrid, 0);
	sdp_list_free(search, 0);

	for (; seq; seq = next) {
		sdp_record_t *rec = (sdp_record_t *) seq->data;
		struct search_context sub_context;

		sdp_printf_service_attr(rec);
		
		
		/*
		if (context->tree) {
			/* Display full tree 
			sdp_printf_service_attr(rec);
		} else {
			/* Display user friendly form 
			print_service_attr(rec);
		}
		*/
		
		printf("\n");
		
		if (sdp_get_group_id(rec, &sub_context.group) != -1) {
			/* Set the subcontext for browsing the sub tree */
			memcpy(&sub_context, &context, sizeof(struct search_context));
			/* Browse the next level down if not done */
			//if (sub_context.group.value.uuid16 != context.group.value.uuid16)
				//do_search(bdaddr, &sub_context);
		}
		next = seq->next;
		free(seq);
		sdp_record_free(rec);
	}
	sdp_close(sess);
	return 0;
}
