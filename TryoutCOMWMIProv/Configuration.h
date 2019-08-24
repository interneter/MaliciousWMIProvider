#pragma once
#include "BaseTypes.h"

typedef struct dict_entry_s {
	char *key;
	GenericValue value;
} dict_entry_s;

typedef struct dict_s {
	int len;
	int cap;
	dict_entry_s *entry;
} dict_s, *dict_t;