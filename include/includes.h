#pragma once
//////////////////////////////
#include "../include/includes-module.h"
//////////////////////////////
#include "../submodules/c_stringfn/include/stringfn.h"
//////////////////////////////
#include "../include/includes-base.h"
//////////////////////////////
#include "../deps/b64/b64.h"
#include "../submodules/ansicodes/ansicodes.h"
#include "../submodules/log.c/src/log.h"
//////////////////////////////
#include "../submodules/c_fsio/include/fsio.h"
//////////////////////////////
//////////////////////////////
#include "../deps/bytes/bytes.h"
#include "../deps/commander/commander.h"
#include "../deps/fs/fs.h"
#include "../deps/hash/hash.h"
#include "../deps/hmac-sha256/hmac-sha256.h"
#include "../deps/list/list.h"
#include "../deps/rhash_md5/md5.h"
#include "../deps/strsplit/strsplit.h"
#include "../deps/timestamp/timestamp.h"
//////////////////////////////
#include "../submodules/assertf.h/assertf.h"
#include "../submodules/c_string_buffer/include/stringbuffer.h"
#include "../submodules/chan/src/chan.h"
#include "../submodules/chan/src/queue.h"
#include "../submodules/csplit/csplit.h"
#include "../submodules/dbg.h/dbg.h"
#include "../submodules/djbhash/src/djbhash.h"
#include "../submodules/generic-print/print.h"
#include "../submodules/kat/include/highlight.h"
#include "../submodules/kat/include/optparse.h"
#include "../submodules/parson/parson.h"
#include "../submodules/subprocess.h/subprocess.h"
#include "../submodules/tinydir/tinydir.h"
#include "../submodules/uuid4/src/uuid4.h"
//////////////////////////////
#include "../submodules/c_scriptexec/include/scriptexec.h"
//////////////////////////////
#include "../include/rvfs.h"
//////////////////////////////
#define OK(MSG)    { fprintf(stderr, "  \e[32m\u2713 \e[90mOK- %s\e[0m\n", MSG); }
//////////////////////////////
