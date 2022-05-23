#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct RVFS_FILE_STRUCT {
  uint32_t                filepath_length;
  char                    *filepath;
  uint32_t                name_length;
  char                    *name;
  uint8_t                 is_directory;
  uint32_t                size;
  uint8_t                 *bytes;
  uint32_t                children_length;
  uint8_t                 is_compressed;
  uint8_t                 is_encrypted;
  struct RVFS_FILE_STRUCT *children;
} RVFSFile;

void rvfs_create_from(RVFSFile *f, const char *filepath, const char *name);
void rvfs_write(RVFSFile *f, const char *filepath);
void rvfs_read(RVFSFile *f, const char *filepath);
void rvfs_from_bytes(RVFSFile *f, uint8_t *raw_bytes, uint32_t len);
void rvfs_extract(RVFSFile *f, const char *filepath);
RVFSFile *rvfs_get_file(RVFSFile *f, const char *filepath);
struct StringFNStrings rvfs_get_files(RVFSFile *f, const char *filepath);
void rvfs_free(RVFSFile *f);
int rvfs_show(RVFSFile *f);

