// MESON_BIN_ENABLED=true
#include "../src/module1.c"

int clean();
int work();
int init();

module(module1) * module1;
module(module1internal) * module1internal;


int init(){
  log_debug("require(module1internal)->value:%d", require(module1internal)->value);

  module1         = require(module1);
  module1internal = require(module1internal);
  return(0);
}


int work(){
  log_debug("module1internal->value:%d", module1internal->value);
  log_info("default mode: %d", module1->mode);

  module1->mode = LOGGER_DEBUG;
  log_info("cur mode: %d", module1->mode);
  module1->info("module1> info1");
  module1->error("module1> error1");
  module1->debug("module1> debug1");

  module1->mode = LOGGER_ERROR;
  log_info("cur mode: %d", module1->mode);
  module1->info("module1> info2");
  module1->error("module1> error2");
  module1->debug("module1> debug2");

  log_debug("module1->module1getvalue(): %d", module1->module1getvalue());
  log_debug("module1->module1setvalue(100): %d", module1->module1setvalue(100));
  log_debug("module1->module1getvalue(): %d", module1->module1getvalue());

  log_debug("module1> debug2");


//  log_info("module1a> cur mode: %d", module1a->mode);
//  log_debug("module1a->module1getvalue(): %d", module1a->module1getvalue());

  log_debug("module1internal->value:%d", module1internal->value);

  module1internal->value = 300;
  log_debug("module1internal->value:%d", module1internal->value);

  log_debug("require(module1internal)->value:%d", require(module1internal)->value);
  assert(clean() == 0);
  // log_info("module1a> cur mode: %d", module1a->mode);
//  log_debug("module1a->module1getvalue(): %d", module1a->module1getvalue());
//clib_module_free(module1a);


  return(0);
}


int clean(){
  clib_module_free(module1);
  log_debug("require(module1internal)->value:%d", require(module1internal)->value);
  log_debug("require(module1internal)->value = 2:%d", (require(module1internal)->value = 2));
  log_debug("require(module1internal)->value:%d", require(module1internal)->value);

  clib_module_deinit(module1internal);
  log_debug("after deinit> require(module1internal)->value:%d", require(module1internal)->value);

  clib_module_free(require(module1internal));
  log_debug("after free> require(module1internal)->value:%d", require(module1internal)->value);
  log_debug("require(module1internal)->value = 2:%d", (require(module1internal)->value = 2));
  log_debug("require(module1internal)->value:%d", require(module1internal)->value);
  return(0);
}


int main(void) {
  assert(init() == 0);
  assert(work() == 0);


  return(0);
}

