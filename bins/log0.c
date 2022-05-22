// MESON_BIN_ENABLED=true
#include "../src/includes.c"


//////////////////////////////////////


int main(const int argc, const char **argv){
  char *s = "test123";

  dbg(s, %s);
  log_error("some err id: %d\n", 12345);

  OK(AC_RESETALL AC_BLUE "Done" AC_RESETALL);
  return(0);
}
