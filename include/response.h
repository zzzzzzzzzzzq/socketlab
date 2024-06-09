#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <sys/mman.h>
#include "parse.h"
#include <arpa/inet.h>
#include <time.h>
#define res_size 1024

typedef enum TYPE{
	HTML,
	CSS,
	PNG,
	JPEG,
	GIF,
	ICO,
	NONE
}TYPE;