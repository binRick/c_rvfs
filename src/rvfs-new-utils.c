#pragma once
#include "../include/rvfs-new-utils.h"
#include "../src/includes.c"


unsigned rvfs_get_path_filenames_qty(char *path){
  return(rvfs_get_path_filenames(path).count);
}

struct StringFNStrings rvfs_get_path_filenames(char *path) {
  struct StringFNStrings rvfs_filenames = { .count = 0 };

  if (!fsio_file_exists(path)) {
    log_error("Invalid path '%s', expected a rvfs archive file", path);
    return(rvfs_filenames);
  }

  long path_size = fsio_file_size(path);

  if (path_size < 1) {
    log_error("Invalid path '%s', expected a valid rvfs archive file", path);
    return(rvfs_filenames);
  }

  rvfs_filenames = stringfn_split("123;321;123", ';');
  log_info("returning %d files from %lu byte file %s", rvfs_filenames.count, path_size, path);
  return(rvfs_filenames);
}

