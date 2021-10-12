# rvfs
> Read-only virtual file system


## usage

``` C

// Populates a RVFSFile struct with recursive content of directory,
// including files in it.
void rvfs_create_from(RVFSFile *f, const char *filepath, const char *name);

// Write a rvfs archive
void rvfs_write(RVFSFile *f, const char *filepath);

// Read a rvfs archive from disk
void rvfs_read(RVFSFile *f, const char *filepath);

// Extract the contents of an rvfs archive to disk
void rvfs_extract(RVFSFile *f, const char *filepath);

// free & deallocate RVFSFile struct.
void rvfs_free(RVFSFile *f);

```

## Linking a .rvfs file into your library or executable
> First convert the .rvfs file to a .o file
``` bash
objcopy -B i386 -I binary -O elf32-i386 <your-file>.rvfs <your-file>.o
```
> Then you can link it to your lib/executable and access the data like this:

``` C
extern uint8_t foo_data[]      asm("_binary_foo_data_bin_start");
extern uint8_t foo_data_size[] asm("_binary_foo_data_bin_size");
extern uint8_t foo_data_end[]  asm("_binary_foo_data_bin_end");


int main(int argc, char* argv[]) {
    size_t foo_size = (size_t)((void *)foo_data_size);
    void  *foo_copy = malloc(foo_size);
    assert(foo_copy);
    memcpy(foo_copy, foo_data, foo_size);
    
    // foo_copy should now be an instance of `RVFSFile`.
    RVFSFile* rvfs_file = (RVFSFile*)foo_copy;
}
```
> "foo" in this case would be what you named your .o file.

## .rvfs file format specification
> The file contains the following fields:

``` C
typedef struct RVFS_FILE_STRUCT {
  uint32_t filepath_length;         // length of filepath in bytes
  char *filepath;                   // path to where the file was loaded from
  uint32_t name_length;             // length of name in bytes
  char *name;                       // name of file without path
  uint8_t is_directory;             // is it a directory or not? (1 / 0)
  uint32_t size;                    // length of the `bytes` field following
  uint8_t *bytes;                   // file contents
  uint32_t children_length;         // how many children this node has
  struct RVFS_FILE_STRUCT *children // list of children;
} RVFSFile;
```