/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2014, Menglong TAN <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

/**
 * 
 *
 * @file dict.c
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Mon Apr 21 15:15:50 2014
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include "fault.h"
#include "dict.h"

static const int size_table[] = {
  2, 5, 11, 23, 47, 97, 197, 397, 797,  /* double upto here */
  1201,   1597,
  2411,   3203,
  4813,   6421,
  9643,   12853,
  19289,  25717,
  51437,
  102877,
  205759,
  411527,
  823117,
  1646237,
  3292489,
  6584983,
  13169977,
  26339969,
  52679969,
  -1
};

dict_t* dict_new(char* name, int size, dict_func_t func) {
  dict_t* dict;

  dict = (dict_t*)malloc(sizeof(dict_t));

  if (dict == NULL) {
    CRY("bad alloc");
    return NULL;
  }

  dict = dict_init(dict, name, size, func);
  dict->is_alloc = 1;

  return dict;
}

dict_t* dict_init(dict_t* dict, char* name, int size, dict_func_t func) {
  int sz;
  int idx = 0;

  while (size_table[idx] != -1 && size_table[idx] < size) {
    idx++;
  }
  if (size_table[idx] == -1) {
    PANIC("panic: too large hash table size (%d)", size);
  }

  size = size_table[idx];
  sz = size * sizeof(dict_hash_bucket_t*);

  dict->bucket = (dict_hash_bucket_t**)malloc(sz);
  memset(dict->bucket, 0, sz);

  dict->is_alloc = 0;
  dict->name = name;
  dict->func = func;
  dict->size = size;
  dict->size80percent = (4 * dict->size) / 5;
  dict->size_table_index = idx;
  dict->used = 0;

  return dict;
}

void dict_delete(dict_t* dict) {
  int i;
  dict_hash_bucket_t* b;
  dict_hash_bucket_t* tmp;
  for (i = 0; i < dict->size; i++) {
    b = dict->bucket[i];
    while (b != NULL) {
      tmp = b->next;
      dict->func.free(b->data);
      b->data = NULL;
      free(b);
      b = tmp;
    }
  }
  free(dict->bucket);
  dict->bucket = NULL;
  free(dict);
}

static void rehash(dict_t* dict, int grow) {
  int sz;
  int old_size = dict->size;
  dict_hash_bucket_t** new_bucket;

  if (grow) {
    if (size_table[dict->size_table_index + 1] == -1) {
      return;
    }
    dict->size_table_index++;
  } else {
    if (dict->size_table_index == 0) {
      return;
    }
    dict->size_table_index--;
  }
  dict->size = size_table[dict->size_table_index];
  dict->size80percent = 4 * dict->size / 5;
  sz = dict->size * sizeof(dict_hash_bucket_t*);
  new_bucket = (dict_hash_bucket_t**)malloc(sz);

  if (dict == NULL) {
    PANIC("bad alloc");
  }

  memset(new_bucket, 0, sz);

  dict->used = 0;

  int i;
  for (i = 0; i < old_size; i++) {
    dict_hash_bucket_t* b = dict->bucket[i];
    while (b != NULL) {
      dict_hash_bucket_t* b_next = b->next;
      int ix = b->hvalue % dict->size;
      if (new_bucket[ix] == NULL) {
        dict->used++;
      }
      b->next = new_bucket[ix];
      new_bucket[ix] = b;
      b = b_next;
    }
  }

  free(dict->bucket);
  dict->bucket = new_bucket;
}

void* dict_get(dict_t* dict, void* tmpl) {
  uint64_t hval = dict->func.hash(tmpl);
  int bucket_idx = hval % dict->size;
  dict_hash_bucket_t* b = dict->bucket[bucket_idx];

  while (b != NULL) {
    if ((b->hvalue == hval) && (dict->func.cmp(tmpl, b->data) == 0)) {
      return b->data;
    }
    b = b->next;
  }

  return NULL;
}

void* dict_put(dict_t* dict, void* tmpl) {
  uint64_t hval = dict->func.hash(tmpl);
  int bucket_idx = hval % dict->size;
  dict_hash_bucket_t* b = dict->bucket[bucket_idx];

  while (b != NULL) {
    if ((b->hvalue == hval) && (dict->func.cmp(tmpl, b->data) == 0)) {
      return (void*)b;
    }
    b = b->next;
  }
  b = (dict_hash_bucket_t*)malloc(sizeof(dict_hash_bucket_t));
  if (b == NULL) {
    PANIC("bad alloc");
  }
  b->data = dict->func.alloc(tmpl);
  dict->used++;

  b->hvalue = hval;
  b->next = dict->bucket[bucket_idx];
  dict->bucket[bucket_idx] = b;

  if (dict->used > dict->size80percent) {
    rehash(dict, 1);
  }

  return b->data;
}

void dict_remove(dict_t* dict, void* tmpl) {
  uint64_t hval = dict->func.hash(tmpl);
  int bucket_idx = hval % dict->size;
  dict_hash_bucket_t* b = dict->bucket[bucket_idx];
  dict_hash_bucket_t* pre = NULL;

  while (b != NULL) {
    if ((b->hvalue == hval) && (dict->func.cmp(tmpl, b->data) == 0)) {
      if (pre == NULL) {
        dict->bucket[bucket_idx] = b->next;
      } else {
        pre->next = b->next;
      }
      dict->func.free(b->data);
      b->data = NULL;
      free(b);
      return;
    }
    pre = b;
    b = b->next;
  }
}

void dict_debugstring(dict_t* dict) {
  int i;
  dict_hash_bucket_t *b;
  for (i = 0; i < dict->size; i++) {
    printf("bucket %d: ", i + 1);
    b = dict->bucket[i];
    if (b == NULL) {
      printf("NULL");
    }
    while (b != NULL) {
      if (dict->func.debugstring != NULL) {
        printf("%" PRId64 "={%s}, ", b->hvalue, dict->func.debugstring(b->data));
      } else {
        printf("%" PRId64 "={}, ", b->hvalue);
      }
      b = b->next;
    }
    printf("\n");
  }
}

/* vim: set expandtab shiftwidth=2 tabstop=2: */
