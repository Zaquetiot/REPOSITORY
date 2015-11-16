#ifndef SPLIT_H
#define SPLIT_H

#include <string.h>
#include <stdlib.h>

char **split(char *phrase, const size_t length, const char delimiter, size_t *n_tokens);

#endif
