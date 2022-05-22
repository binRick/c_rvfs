#pragma once
//////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
//////////////////////////////
#include "../submodules/assertf.h/assertf.h"
//////////////////////////////
#include "../include/rvfs.h"
//////////////////////////////
#define OK(MSG){ fprintf(stderr, "  \e[32m\u2713 \e[90mOK- %s\e[0m\n", MSG); }
//////////////////////////////
