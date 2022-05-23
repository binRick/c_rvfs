// MESON_BIN_ENABLED=true
#include "../src/includes.c"


int main(void) {
  char buf[UUID4_LEN];

  uuid4_init();
  uuid4_generate(buf);
  printf("%s\n", buf);

  return(EXIT_SUCCESS);
}
