#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include "btlib.h"

struct btdev_name *dev_names;
	
int main(int argc, char **argv)
{
	printf("[%s] Scanning ...\n", argv[0]);
	
	int num_rsp = btdev_scan(100);
	
	int i;
	for(i = 0; i < num_rsp; i++){
		printf("[%s] Info: \t%s\t%s\n", argv[0], dev_names[i].addr, dev_names[i].name);
	}
}
