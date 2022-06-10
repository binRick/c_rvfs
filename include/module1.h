#pragma once
#include "../include/includes.h"

enum module1_mode {
  LOGGER_NONE,
  LOGGER_INFO,
  LOGGER_ERROR,
  LOGGER_DEBUG,
  LOGGER_TRACE,
};

module(module1internal) {
  define(module1internal, CLIB_MODULE);
  enum module1_mode mode;
  int               value;
};

int  module1internal_init(module(module1internal) * exports);
void module1internal_deinit(module(module1internal) * exports);

exports(module1internal) {
  .mode   = LOGGER_TRACE,
  .value  = 669,
  .init   = module1internal_init,
  .deinit = module1internal_deinit,
};


static inline int module1get() {
  return(require(module1internal)->value);
}


static inline int module1set(int val) {
  require(module1internal)->value = val;
  return(0);
}


module(module1) {
  define(module1, CLIB_MODULE);

  enum module1_mode mode;

  void              (*info)(char *);
  void              (*debug)(char *);
  void              (*error)(char *);

  int               (*module1setvalue)(int);
  int               (*module1getvalue)();
};

int  module1_init(module(module1) * exports);
void module1_deinit(module(module1) * exports);

exports(module1) {
  .mode            = LOGGER_TRACE,
  .init            = module1_init,
  .deinit          = module1_deinit,
  .module1getvalue = module1get,
  .module1setvalue = module1set,
};
