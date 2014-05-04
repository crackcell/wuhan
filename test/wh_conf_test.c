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
 * @file wh_conf_test.c
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Fri Apr 25 19:09:25 2014
 *
 **/

#include <stdio.h>
#include <CUnit/Basic.h>

#include <wuhan/wh_conf.h>
#include <dict.h>

static wh_conf_t* conf = NULL;

int init_suite() {
  conf = wh_conf_new();
  return conf == NULL ? -1 : 0;
}

int clean_suite() {
  wh_conf_delete(conf);
  return 0;
}

void test_load() {
  wh_conf_load(conf, "test.conf");
  dict_debugstring((dict_t*)(conf->dict));
}

void test_get_int() {
  printf("{int key:%d}\n", wh_conf_get_int(conf, "int key"));
}

void test_get_str() {
  printf("{trim key4:%s}\n", wh_conf_get_str(conf, "trim key4"));
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

  if ((NULL == CU_add_test(suite, "test of wh_conf_load()", test_load)) ||
      (NULL == CU_add_test(suite, "test of wh_conf_get_int()", test_get_int)) ||
      (NULL == CU_add_test(suite, "test of wh_conf_get_str()", test_get_str))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

/* vim: set expandtab shiftwidth=2 tabstop=2: */
