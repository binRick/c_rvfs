#pragma once
//////////////////////////////
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#define DBG_H_DEF_ONCE
#define DBG_H_NO_WARNING
#define ASSERTF_DEF_ONCE
//////////////////////////////
#include "../include/includes-base.h"
//////////////////////////////
#include "../deps/b64/b64.h"
//////////////////////////////
#include "../submodules/c_fsio/include/fsio.h"
#include "../submodules/c_stringfn/include/stringfn.h"
//////////////////////////////
#include "../deps/commander/commander.h"
#include "../deps/fs/fs.h"
#include "../deps/list/list.h"
#include "../deps/rhash_md5/md5.h"
#include "../deps/strsplit/strsplit.h"
#include "../deps/timestamp/timestamp.h"
//////////////////////////////
#include "../submodules/assertf.h/assertf.h"
#include "../submodules/c_string_buffer/include/stringbuffer.h"
#include "../submodules/csplit/csplit.h"
#include "../submodules/csplit/csplit.h"
#include "../submodules/dbg.h/dbg.h"
#include "../submodules/djbhash/src/djbhash.h"
#include "../submodules/generic-print/print.h"
#include "../submodules/parson/parson.h"
#include "../submodules/subprocess.h/subprocess.h"
//////////////////////////////
#include "../submodules/c_scriptexec/include/scriptexec.h"
//////////////////////////////
#include "../include/rvfs.h"
//////////////////////////////
#define OK(MSG)    { fprintf(stderr, "  \e[32m\u2713 \e[90mOK- %s\e[0m\n", MSG); }
//////////////////////////////