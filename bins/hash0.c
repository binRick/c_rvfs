// MESON_BIN_ENABLED=true
#include "../src/includes.c"


int main(void) {
  char buf[UUID4_LEN];

  uuid4_init();
  uuid4_generate(buf);
  log_info("uuid>%s", buf);


  hash_t *hash = hash_new();

  hash_set(hash, "name", "tobi");
  hash_set(hash, "species", "ferret");
  hash_set(hash, "age", "2");


  hash_each(hash, {
    printf("each>%s: %s\n", key, (char *)val);
  });
  hash_each_key(hash, {
    printf("key>%s\n", key);
  });
  hash_each_val(hash, {
    printf("val>%s\n", (char *)val);
  });

  hash_free(hash);


  return(EXIT_SUCCESS);
}
