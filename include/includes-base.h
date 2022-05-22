#pragma once
//////////////////////////////
#include <assert.h>
#include <dirent.h>
#include <err.h>
#include <errno.h>
#include <getopt.h>
#include <glob.h>
#include <inttypes.h>
#include <libgen.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sysexits.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>
#include <wctype.h>
//////////////////////////////
#define OK(MSG)    { fprintf(stderr, "  \e[32m\u2713 \e[90mOK- %s\e[0m\n", MSG); }
//////////////////////////////
