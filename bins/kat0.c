// MESON_BIN_ENABLED=true
#include "../src/includes.c"
#include <unistd.h>

INLINE extern char * add_char_to_hl(char *, char);
INLINE extern char * add_str_to_hl(char *, const char *, size_t);


int main(const int argc, const char **argv){
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    OK("Test OK"); return(0);
  }

  FILE                    *fp = stdin;        /* File pointer.                     */
  char                    *line;              /* Current line.                     */
  size_t                  len;                /* Allocated size.                   */
  ssize_t                 read;               /* Bytes read.                       */
  char                    *hl;                /* Currently highlighted line.       */
  char                    *buff;              /* Buffer to be dumped.              */
  char                    *theme_file = NULL; /* Theme file.                       */
  struct highlighted_line *high;              /* Highlighted line structure. */

  if (argc > 1) {
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
      fprintf(stderr, "%s: cannot open the file %s, is it really exists?\n",
              argv[0], argv[1]);
      return(1);
    }
  }

  line = NULL;
  buff = NULL;
  len  = 0;

  if (highlight_init(theme_file) < 0) {
    if (fp != stdin) {
      fclose(fp);
    }
    return(-1);
  }

  hl   = highlight_alloc_line();
  buff = highlight_alloc_line();

  while ((read = getline(&line, &len, fp)) != -1) {
    hl   = highlight_line(line, hl, read);
    high = ((struct highlighted_line *)hl - 1);
    buff = add_str_to_hl(buff, hl, high->idx - 1);
  }

  buff = add_char_to_hl(buff, '\0');
  high = ((struct highlighted_line *)buff - 1);
  write(fileno(stdout), buff, high->idx - 1);

  highlight_free(hl);
  highlight_free(buff);
  free(line);

  if (fp != stdin) {
    fclose(fp);
  }

  highlight_finish();
} /* main */
