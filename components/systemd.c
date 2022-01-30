/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <string.h>

#include "../util.h"

const char *
systemd_is_active(const char *service)
{
	char *p;
	FILE *fp;
	char cmd[2048];

	if (esnprintf(cmd, sizeof(cmd), "systemctl is-active %s", service) < 0) {
		return NULL;
	}

	if (!(fp = popen(cmd, "r"))) {
		warn("popen '%s':", cmd);
		return NULL;
	}
	p = fgets(buf, sizeof(buf) - 1, fp);
	if (pclose(fp) < 0) {
		warn("pclose '%s':", cmd);
		return NULL;
	}
	if (!p) {
		return NULL;
	}
	if ((p = strrchr(buf, '\n'))) {
		p[0] = '\0';
	}

	if (!buf[0]) {
		return NULL;
	}

	return !strcmp(buf, "active") ?  "^c#d70751^°" : "^c#a3b9bf^°" ;
}
