#include "../src/includes.c"


static int extract(const char *inputfile, const char *destdir) {
  RVFSFile rf = {};

  rvfs_read(&rf, inputfile);
  rvfs_extract(&rf, destdir);
  rvfs_free(&rf);
  return(0);
}


static int package(const char *inputdir, const char *destfile) {
  RVFSFile f = {};

  rvfs_create_from(&f, inputdir, 0);
  rvfs_write(&f, destfile);
  rvfs_free(&f);

  return(0);
}

/*
 * char* get_indent(uint32_t n) {
 * char* buff = (char*)calloc(n+1, sizeof(char));
 * memset(buff, '\t', n);
 * return buff;
 * }*/


static int find(const char *inputfile, const char *path) {
  RVFSFile rf = {};

  rvfs_read(&rf, inputfile);
  RVFSFile *f = rvfs_get_file(&rf, path);

  if (f) {
    printf("is_dir\tsize\tname\n");
    printf("%d\t%d\t%s\n", f->is_directory, f->size, f->name ? f->name : f->filepath ? f->filepath : "N/A");
  } else {
    printf("Not found.\n");
  }
  rvfs_free(&rf);
  return(0);
}


static int show(const char *filepath) {
  RVFSFile rf = {};

  rvfs_read(&rf, filepath);
  rvfs_show(&rf);
  rvfs_free(&rf);
  return(0);
}

