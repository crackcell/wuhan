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
 * @file wh_conf_example.c
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Fri Apr 25 19:09:25 2014
 *
 **/

#include <stdio.h>
#include <wuhan/wh_conf.h>
#include <dict.h>

int main(int argc, char *argv[]) {
  // 1. New
  wh_conf_t* conf = wh_conf_new();

  // 2. Load file
  wh_conf_load(conf, "test.conf");
  dict_debugstring((dict_t*)(conf->dict));

  // 3. Get int
  printf("{int key:%d}\n", wh_conf_get_int(conf, "int key"));

  // 4. Get str
  printf("{trim key4:%s}\n", wh_conf_get_str(conf, "trim key4"));

  wh_conf_delete(conf);
  return 0;
}

/* vim: set expandtab shiftwidth=2 tabstop=2: */
