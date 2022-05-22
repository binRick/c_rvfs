// MESON_BIN_ENABLED=true
/////////////////////////////////////////////
#include "../include/rvfs-new-utils.h"
#include "../src/includes.c"
#include "../src/rvfs-new-utils.c"
/////////////////////////////////////////////
char *cmd;


/////////////////////////////////////////////
static int print_help() {
  printf(
    "Usage:\n"
    "\t rvfs <command>\n\n"
    "Commands:\n"
    "\t filenames <inputfile>\n"
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

  cmd = argv[1];

  if (argc < 2) {
    return(print_help());
  }

  if (strcmp(cmd, "filesqty") == 0) {
    if (argc < 3) {
      return(print_help());
    }
    log_info("getting filenames qty from %s............", argv[2]);
    unsigned qty = rvfs_get_path_filenames_qty(argv[2]);
    log_info("\tgot %d files", qty);
    if (qty > 0) {
      return(0);
    }else{
      return(1);
    }
  }
  if (strcmp(cmd, "filenames") == 0) {
    if (argc < 3) {
      return(print_help());
    }
    log_info("getting filenames from %s............", argv[2]);
    struct StringFNStrings rvfs_filenames = rvfs_get_path_filenames(argv[2]);
    log_info("\tgot %d files", rvfs_filenames.count);
    return(0);
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
} /* main */
