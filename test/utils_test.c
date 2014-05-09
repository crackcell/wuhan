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
 * @file util_test.c
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Fri Apr 25 21:58:23 2014
 *
 **/

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include <CUnit/Basic.h>

#include <utils.h>

int init_suite() { return 0; }

int clean_suite() { return 0; }

void test_trim() {
  char line[] = "  this is a test  ";
  char* p = trim(line);
  CU_ASSERT(strcmp(p, "this is a test") == 0);
}

void test_ms_since_epoch() {
  printf("ms_since_epoch: %" PRId64 "\n", ms_since_epoch());
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

  if ((NULL == CU_add_test(suite, "test of trim()", test_trim)) ||
      (NULL == CU_add_test(suite, "test of ms_since_epoch()", test_ms_since_epoch))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

/* vim: set expandtab shiftwidth=2 tabstop=2: */
