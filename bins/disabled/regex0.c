// MESON_BIN_ENABLED=false
//////////////////////////////////
#include "../src/includes.c"
//////////////////////////////////


#define _OK     ((char *)1)
#define _NOK    ((char *)0)


char *test_vector[][4] = {
  { _OK,  "\\d",                       "5",                      (char *)1  },
  { _OK,  "\\w+",                      "hej",                    (char *)3  },
  { _OK,  "\\s",                       "\t \n",                  (char *)1  },
  { _NOK, "\\S",                       "\t \n",                  (char *)0  },
  { _OK,  "[\\s]",                     "\t \n",                  (char *)1  },
  { _NOK, "[\\S]",                     "\t \n",                  (char *)0  },
  { _NOK, "\\D",                       "5",                      (char *)0  },
  { _NOK, "\\W+",                      "hej",                    (char *)0  },
  { _OK,  "[0-9]+",                    "12345",                  (char *)5  },
  { _OK,  "\\D",                       "hej",                    (char *)1  },
  { _NOK, "\\d",                       "hej",                    (char *)0  },
  { _OK,  "[^\\w]",                    "\\",                     (char *)1  },
  { _OK,  "[\\W]",                     "\\",                     (char *)1  },
  { _NOK, "[\\w]",                     "\\",                     (char *)0  },
  { _OK,  "[^\\d]",                    "d",                      (char *)1  },
  { _NOK, "[\\d]",                     "d",                      (char *)0  },
  { _NOK, "[^\\D]",                    "d",                      (char *)0  },
  { _OK,  "[\\D]",                     "d",                      (char *)1  },
  { _OK,  "^.*\\\\.*$",                "c:\\Tools",              (char *)8  },
  { _OK,  "^[\\+-]*[\\d]+$",           "+27",                    (char *)3  },
  { _OK,  "[abc]",                     "1c2",                    (char *)1  },
  { _NOK, "[abc]",                     "1C2",                    (char *)0  },
  { _OK,  "[1-5]+",                    "0123456789",             (char *)5  },
  { _OK,  "[.2]",                      "1C2",                    (char *)1  },
  { _OK,  "a*$",                       "Xaa",                    (char *)2  },
  { _OK,  "a*$",                       "Xaa",                    (char *)2  },
  { _OK,  "[a-h]+",                    "abcdefghxxx",            (char *)8  },
  { _NOK, "[a-h]+",                    "ABCDEFGH",               (char *)0  },
  { _OK,  "[A-H]+",                    "ABCDEFGH",               (char *)8  },
  { _NOK, "[A-H]+",                    "abcdefgh",               (char *)0  },
  { _OK,  "[^\\s]+",                   "abc def",                (char *)3  },
  { _OK,  "[^fc]+",                    "abc def",                (char *)2  },
  { _OK,  "[^d\\sf]+",                 "abc def",                (char *)3  },
  { _OK,  "\n",                        "abc\ndef",               (char *)1  },
  { _OK,  "b.\\s*\n",                  "aa\r\nbb\r\ncc\r\n\r\n", (char *)4  },
  { _OK,  ".*c",                       "abcabc",                 (char *)6  },
  { _OK,  ".+c",                       "abcabc",                 (char *)6  },
  { _OK,  "[b-z].*",                   "ab",                     (char *)1  },
  { _OK,  "b[k-z]*",                   "ab",                     (char *)1  },
  { _NOK, "[0-9]",                     "  - ",                   (char *)0  },
  { _OK,  "[^0-9]",                    "  - ",                   (char *)1  },
  { _OK,  "0|",                        "0|",                     (char *)2  },
  { _NOK, "\\d\\d:\\d\\d:\\d\\d",      "0s:00:00",               (char *)0  },
  { _NOK, "\\d\\d:\\d\\d:\\d\\d",      "000:00",                 (char *)0  },
  { _NOK, "\\d\\d:\\d\\d:\\d\\d",      "00:0000",                (char *)0  },
  { _NOK, "\\d\\d:\\d\\d:\\d\\d",      "100:0:00",               (char *)0  },
  { _NOK, "\\d\\d:\\d\\d:\\d\\d",      "00:100:00",              (char *)0  },
  { _NOK, "\\d\\d:\\d\\d:\\d\\d",      "0:00:100",               (char *)0  },
  { _OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "0:0:0",                  (char *)5  },
  { _OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "0:00:0",                 (char *)6  },
  { _OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "0:0:00",                 (char *)5  },
  { _OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "00:0:0",                 (char *)6  },
  { _OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "00:00:0",                (char *)7  },
  { _OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "00:0:00",                (char *)6  },
  { _OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "0:00:00",                (char *)6  },
  { _OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "00:00:00",               (char *)7  },
  { _OK,  "[Hh]ello [Ww]orld\\s*[!]?", "Hello world !",          (char *)12 },
  { _OK,  "[Hh]ello [Ww]orld\\s*[!]?", "hello world !",          (char *)12 },
  { _OK,  "[Hh]ello [Ww]orld\\s*[!]?", "Hello World !",          (char *)12 },
  { _OK,  "[Hh]ello [Ww]orld\\s*[!]?", "Hello world!   ",        (char *)11 },
  { _OK,  "[Hh]ello [Ww]orld\\s*[!]?", "Hello world  !",         (char *)13 },
  { _OK,  "[Hh]ello [Ww]orld\\s*[!]?", "hello World    !",       (char *)15 },
  { _NOK, "\\d\\d?:\\d\\d?:\\d\\d?",   "a:0",                    (char *)0  }, /* Failing test case reported in https://github.com/kokke/tiny-regex-c/issues/12 */
/*
 * { _OK,  "[^\\w][^-1-4]",     ")T",          (char*) 2      },
 * { _OK,  "[^\\w][^-1-4]",     ")^",          (char*) 2      },
 * { _OK,  "[^\\w][^-1-4]",     "*)",          (char*) 2      },
 * { _OK,  "[^\\w][^-1-4]",     "!.",          (char*) 2      },
 * { _OK,  "[^\\w][^-1-4]",     " x",          (char*) 2      },
 * { _OK,  "[^\\w][^-1-4]",     "$b",          (char*) 2      },
 */
  { _OK,  ".?bar",                     "real_bar",               (char *)4  },
  { _NOK, ".?bar",                     "real_foo",               (char *)0  },
  { _NOK, "X?Y",                       "Z",                      (char *)0  },
  { _OK,  "[a-z]+\nbreak",             "blahblah\nbreak",        (char *)14 },
  { _OK,  "[a-z\\s]+\nbreak",          "bla bla \nbreak",        (char *)14 },
};


void re_print(re_t);


int main(){
  char   *text;
  char   *pattern;
  int    should_fail;
  int    length;
  int    correctlen;
  size_t ntests  = sizeof(test_vector) / sizeof(*test_vector);
  size_t nfailed = 0;
  size_t i;

  for (i = 0; i < ntests; ++i) {
    pattern     = test_vector[i][1];
    text        = test_vector[i][2];
    should_fail = (test_vector[i][0] == _NOK);
    correctlen  = (int)(test_vector[i][3]);

    int m = re_match(pattern, text, &length);

    if (should_fail) {
      if (m != (-1)) {
        printf("\n");
        re_print(re_compile(pattern));
        fprintf(stderr, "[%lu/%lu]: pattern '%s' matched '%s' unexpectedly, matched %i chars. \n", (i + 1), ntests, pattern, text, length);
        nfailed += 1;
      }
    }else {
      if (m == (-1)) {
        printf("\n");
        re_print(re_compile(pattern));
        fprintf(stderr, "[%lu/%lu]: pattern '%s' didn't match '%s' as expected. \n", (i + 1), ntests, pattern, text);
        nfailed += 1;
      }else if (length != correctlen) {
        fprintf(stderr, "[%lu/%lu]: pattern '%s' matched '%i' chars of '%s'; expected '%i'. \n", (i + 1), ntests, pattern, length, text, correctlen);
        nfailed += 1;
      }
    }
  }

  // printf("\n");
  printf("%lu/%lu tests succeeded.\n", ntests - nfailed, ntests);
  printf("\n");
  printf("\n");
  printf("\n");

  return(nfailed);  /* 0 if all tests passed */
} /* main */
