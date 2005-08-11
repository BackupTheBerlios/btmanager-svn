#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

#include <termios.h>
#include <fcntl.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#include "btlib.h"
	
int btdev_scan(int num_rsp)
{
	int dev_id = -1;
	inquiry_info *info = NULL;
	int length, flags;
	char addr[18];
	char name[248];
	int i, opt, dd;
	
	length  = 8;  /* ~10 seconds */
	flags = 0;

	if (dev_id < 0) {
		dev_id = hci_get_route(NULL);
		if (dev_id < 0) {
			perror("Device is not available");
			exit(1);
		}
	}

	num_rsp = hci_inquiry(dev_id, length, num_rsp, NULL, &info, flags);
	if (num_rsp < 0) {
		perror("Inquiry failed");
		exit(1);
	}

	dd = hci_open_dev(dev_id);
	if (dd < 0) {
		perror("HCI device open failed");
		free(info);
		exit(1);
	}
	
	dev_names = malloc(sizeof(struct btdev_name) * 10);
		
	for (i = 0; i < num_rsp; i++) {
		memset(name, 0, sizeof(name));
		if (hci_read_remote_name(dd, &(info+i)->bdaddr, sizeof(name), name, 100000) < 0)
			strcpy(name, "n/a");
		ba2str(&(info+i)->bdaddr, addr);
		strcpy(dev_names[i].addr, addr);
		strcpy(dev_names[i].name, name);
	}

	close(dd);
	free(info);
	return num_rsp;
}
