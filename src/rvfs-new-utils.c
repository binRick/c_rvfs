#pragma once
#include "../include/rvfs-new-utils.h"
#include "../src/includes.c"
#include "../src/rvfs.c"

#define NEW_RVFS_FILES_LIST \
  {                         \
    .count = 0,             \
  }


unsigned rvfs_get_path_filenames_qty(char *path){
  return(rvfs_get_path_filenames(path).count);
}


int tinydir_demo(char *path){
  tinydir_dir dir;

  if (tinydir_open(&dir, path) == -1) {
    perror("Error opening file");
    goto bail;
  }

  while (dir.has_next) {
    tinydir_file file;
    if (tinydir_readfile(&dir, &file) == -1) {
      perror("Error getting file");
      goto bail;
    }
    if ((strcmp(file.name, ".") == 0) || (strcmp(file.name, "..") == 0)) {
    }else{
      log_info(
        "<tinydir> Name: " AC_RESETALL AC_YELLOW "%25s" AC_RESETALL
        "|"
        "Dir? " AC_RESETALL AC_BLUE "%3s" AC_RESETALL
        "|",
        file.name,
        file.is_dir ? "Yes" : "No"
        );
    }
    if (tinydir_next(&dir) == -1) {
      perror("Error getting next file");
      goto bail;
    }
  }

bail:
  tinydir_close(&dir);
  return(0);
}


int rvfs_recursive_children_qty(RVFSFile *f, char *filepath) {
  int qty = 0;

  if (f == 0) {
    rvfs_read(f, filepath);
    if (f == 0) {
      return(1);
    }
  }
  log_debug("recursive children for path '%s': %d children", filepath, f->children_length);
  if (f->children && f->children_length) {
    for (uint32_t i = 0; i < f->children_length; i++) {
      RVFSFile child    = f->children[i];
      char     *newpath = (char *)calloc((filepath ? strlen(filepath) : 0) + strlen(child.name) + 16, sizeof(char));

      if (filepath) {
        strcat(newpath, filepath);
        strcat(newpath, "/");
      }
      strcat(newpath, child.name);
      qty++;
    }
  }
  return(qty);
}

struct StringFNStrings rvfs_get_path_filenames(char *path) {
  struct StringFNStrings rvfs_filenames = NEW_RVFS_FILES_LIST;

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
  /*
   * RVFSFile *r = malloc(sizeof(RVFSFile));
   * rvfs_recursive_children_qty(r, path);
   * log_info("children_length: %d\n", r->children_length);
   * rvfs_free(r);
   */
  log_info("returning %d files from %lu byte file %s", rvfs_filenames.count, path_size, path);
  tinydir_demo(".");
  return(rvfs_filenames);
}

