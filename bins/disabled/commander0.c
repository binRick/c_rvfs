#include "../include/includes.h"
// MESON_BIN_ENABLED=true


static void verbose() {
  printf("verbose: enabled\n");
}


static void required(command_t *self) {
  printf("required: %s\n", self->arg);
}


static void test_mode(command_t *self) {
  printf("OK\n");
}


static void optional(command_t *self) {
  printf("optional: %s\n", self->arg);
}


int main(int argc, char **argv) {
  command_t cmd;

  command_init(&cmd, argv[0], "0.0.1");
  command_option(&cmd, "-v", "--verbose", "enable verbose stuff", verbose);
  command_option(&cmd, "-t", "--test", "test mode", test_mode);
  command_option(&cmd, "-r", "--required <arg>", "required arg", required);
  command_option(&cmd, "-o", "--optional [arg]", "optional arg", optional);
  command_parse(&cmd, argc, argv);
  printf("additional args:\n");
  for (int i = 0; i < cmd.argc; ++i) {
    printf("  - '%s'\n", cmd.argv[i]);
  }
  command_free(&cmd);
  return(0);
}
