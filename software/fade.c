#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <stdint.h>
#include <string.h>

#include "led-mod.h"

int main(int argc, char *argv[])
{
	int fd, ret;
	struct color rgb={0,0,0};
	int i, j;
	char seq[]="BGbRBgbr";

	fd=open("/dev/led",O_WRONLY);
	if (fd<0) {
		perror("open");
		return 1;
	}
	while (1) {
		for (j=0;j<strlen(seq);j++) {
			for (i=0;i<0x7ff;i+=16) {
				if (seq[j]=='R') {
					rgb.color_r=i;
				} else if (seq[j]=='G') {
					rgb.color_g=i;
				} else if (seq[j]=='B') {
					rgb.color_b=i;
				} else if (seq[j]=='r') {
					rgb.color_r=0x7FF-i;
				} else if (seq[j]=='g') {
					rgb.color_g=0x7FF-i;
				} else if (seq[j]=='b') {
					rgb.color_b=0x7FF-i;
				}
				ret=ioctl(fd,RGB_LED_SET,&rgb);
				if (ret<0) {
					perror("ioctl");
				}
				usleep(14000);
			}
		}
	}
	close(fd);

	return 0;
}
