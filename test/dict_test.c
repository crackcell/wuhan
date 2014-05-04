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
 * @file dict_test.c
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Tue Apr 22 11:36:38 2014
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <CUnit/Basic.h>

#include <dict.h>

struct dict_item {
  int key;
  int value;
};

uint64_t int_dict_hash(void* item) {
  return ((struct dict_item*)item)->key;
}

int int_dict_cmp(void* item1, void* item2) {
  return ((struct dict_item*)item1)->key == ((struct dict_item*)item2)->key ? 0 : 1;
}

void* int_dict_alloc(void* item) {
  int* p = (int*)malloc(sizeof(struct dict_item));
  memcpy(p, item, sizeof(struct dict_item));
  return p;
}

void int_dict_free(void* item) {
  struct dict_item* p = (struct dict_item*)item;
  free(p);
}

dict_func_t int_dict_func = {.hash = int_dict_hash,
                             .cmp = int_dict_cmp,
                             .alloc = int_dict_alloc,
                             .free = int_dict_free};

static dict_t* int_dict = NULL;

int init_suite() {
  int_dict = dict_new("test", 1, int_dict_func);
  return int_dict == NULL ? -1 : 0;
}

int clean_suite() {
  dict_delete(int_dict);
  return 0;
}

void test_put() {
  struct dict_item tmpl;

  tmpl.key = 1;
  tmpl.value = 1;
  dict_put(int_dict, &tmpl);
  tmpl.key = 12;
  tmpl.value = 12;
  dict_put(int_dict, &tmpl);
  tmpl.key = 13;
  tmpl.value = 13;
  dict_put(int_dict, &tmpl);
  dict_debugstring(int_dict);
  printf("================\n");
}

void test_get() {
  struct dict_item tmpl;

  struct dict_item* item;
  tmpl.key = 1;
  item = (struct dict_item*)dict_get(int_dict, &tmpl);
  printf("{%d:%d}\n", item->key, item->value);

  printf("================\n");
}

void test_remove() {
  struct dict_item tmpl;

  tmpl.key = 1;
  dict_remove(int_dict, &tmpl);
  dict_debugstring(int_dict);

  printf("================\n");
}

int main(int argc, char *argv[]) {
  CU_pSuite suite = NULL;

  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  suite = CU_add_suite("suite", init_suite, clean_suite);
  if (suite == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if ((NULL == CU_add_test(suite, "test of dict_put()", test_put)) ||
      (NULL == CU_add_test(suite, "test of dict_get()", test_get))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

/* vim: set expandtab shiftwidth=2 tabstop=2: */
