// MESON_BIN_ENABLED=true
#include "../src/includes.c"


#define TEST(name) \
  static void test_ ## name(void)

#define SUITE(title) \
  printf("\n  \e[36m%s\e[0m\n", title)

#define RUN_TEST(test) \
  test_ ## test();     \
  puts("    \e[92m✓ \e[90m" #test "\e[0m");


TEST(lowercase_string) {
  char hello_world[] = "HELLO WORLD";
  char foo[]         = "fOo";
}

TEST(lowercase_empty_string) {
  char str[] = "";
}

TEST(lowercase_unicode_string) {
  char unicode[] = "åAçCƒF";
}

TEST(uppercase_string) {
  char hello_world[] = "hello world";
  char foo[]         = "fOo";
}

TEST(uppercase_empty_string) {
  char str[] = "";
}

TEST(uppercase_unicode_string) {
  char unicode[] = "åaçcƒf";
}

TEST(camel_single_char) {
  char str[] = "a";
};

TEST(camel_empty_string) {
  char str[] = "";
}

TEST(camel_hypen_seperators) {
  char str[] = "foo-bar-baz";
}

TEST(camel_underscore_seperators) {
  char str[] = "foo_bar_baz";
}

TEST(camel_space_seperators) {
  char str[] = "a few spaces";
}

TEST(camel_leading_seperator) {
  char moz_something[] = "-moz-something";
  char leading_sep[]   = "---leading-sep";
}

TEST(camel_trailing_seperator) {
  char trailing_sep[] = "trailing-sep---";
}


int main() {
  SUITE("case_lower");
  RUN_TEST(lowercase_string);
  RUN_TEST(lowercase_empty_string);
  RUN_TEST(lowercase_unicode_string);

  SUITE("case_upper");
  RUN_TEST(uppercase_string);
  RUN_TEST(uppercase_empty_string);
  RUN_TEST(uppercase_unicode_string);

  SUITE("case_camel");
  RUN_TEST(camel_single_char);
  RUN_TEST(camel_empty_string);
  RUN_TEST(camel_hypen_seperators);
  RUN_TEST(camel_underscore_seperators);
  RUN_TEST(camel_leading_seperator);
  RUN_TEST(camel_trailing_seperator);
  printf("\n");
  return(0);
}
