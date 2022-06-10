#pragma once
#include "../include/module1.h"


static inline void module1_info(char *message) {
  if (require(module1)->mode >= LOGGER_INFO) {
    fprintf(stdout, " info: %s\n", message);
  }
}


static inline void module1_error(char *message) {
  if (require(module1)->mode >= LOGGER_ERROR) {
    fprintf(stderr, "error: %s\n", message);
  }
}


static inline void module1_debug(char *message) {
  if (require(module1)->mode >= LOGGER_DEBUG) {
    fprintf(stderr, "debug: %s\n", message);
  }
}


void module1internal_deinit(module(module1internal) *exports) {
  printf("module1internal> deinit\n");
  require(module1internal)->value = 200;
}


int module1internal_init(module(module1internal) *exports) {
  printf("module1internal> init\n");
  clib_module_init(module1internal, exports);

  return(0);
}


void module1_deinit(module(module1) *exports) {
  printf("module1> deinit\n");

  clib_module_free(require(module1internal));
  clib_module_deinit(module1);
}


int module1_init(module(module1) *exports) {
  printf("module1> init\n");

  clib_module_init(module1, exports);

  exports->deinit = module1_deinit;

  exports->mode  = LOGGER_NONE;
  exports->info  = module1_info;
  exports->error = module1_error;
  exports->debug = module1_debug;

  return(0);
}

