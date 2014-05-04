/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2014, Menglong TAN <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _DICT_H_
#define _DICT_H_

/**
 *
 *
 * @file dict.h
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Mon Apr 21 11:18:07 2014
 *
 **/

#include <stdint.h>

typedef uint64_t (*dict_hash_func_t)(void* key);
typedef int      (*dict_cmp_func_t)(void* key1, void* key2);
typedef void*    (*dict_alloc_func_t)(void* value);
typedef void     (*dict_free_func_t)(void* value);
typedef char*    (*dict_dbgstr_func_t)(void* value);

typedef struct dict_hash_bucket {
  struct dict_hash_bucket* next;
  uint64_t                 hvalue;
  void*                    data;
} dict_hash_bucket_t;

typedef struct dict_func {
  dict_hash_func_t   hash;
  dict_cmp_func_t    cmp;
  dict_alloc_func_t  alloc;
  dict_free_func_t   free;
  dict_dbgstr_func_t debugstring;
} dict_func_t;

typedef struct dict {
  dict_func_t          func;
  int                  is_alloc;
  char*                name;
  int                  size;             /* Number of slots */
  int                  size80percent;    /* Rehash threshold */
  int                  size_table_index; /* Size in size table */
  int                  used;             /* Number of used buckets */
  dict_hash_bucket_t** bucket;           /* Vector of bucket pointers */
} dict_t;

dict_t* dict_new(char* name, int size, dict_func_t func);
dict_t* dict_init(dict_t* dict, char* name, int size, dict_func_t func);
void    dict_delete(dict_t* dict);

void*   dict_get(dict_t* dict, void* tmpl);
void*   dict_put(dict_t* dict, void* tmpl);
void    dict_remove(dict_t* dict, void* tmpl);

void    dict_debugstring(dict_t* dict);

#endif /* _DICT_H_ */

/* vim: set expandtab shiftwidth=2 tabstop=2: */
