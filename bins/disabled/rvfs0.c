// MESON_BIN_ENABLED=true
#include "../src/includes.c"


static int print_help() {
  printf(
    "Usage:\n"
    "\t rvfs <command>\n\n"
    "Commands:\n"
    "\t extract <inputfile> <destdir>\n"
    "\t package <inputdir> <destfile>\n"
    "\t find <inputfile> <path>\n"
    "\t show <inputfile>\n"
    );

  return(1);
}


int main(int argc, char **argv) {
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    OK("Test OK"); return(0);
  }
  const char *cmd = argv[1];

  if (argc < 2) {
    return(print_help());
  }

  if (strcmp(cmd, "extract") == 0) {
    if (argc < 3) {
      return(print_help());
    }
    return(extract(argv[2], argv[3]));
  }

  if (strcmp(cmd, "package") == 0) {
    if (argc < 3) {
      return(print_help());
    }
    return(package(argv[2], argv[3]));
  }

  if (strcmp(cmd, "show") == 0) {
    if (argc < 2) {
      return(print_help());
    }
    return(show(argv[2]));
  }

  if (strcmp(cmd, "find") == 0) {
    if (argc < 3) {
      return(print_help());
    }
    return(find(argv[2], argv[3]));
  }

  return(print_help());
}
