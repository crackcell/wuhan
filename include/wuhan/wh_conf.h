/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2014, Menglong TAN <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _WH_CONF_H_
#define _WH_CONF_H_

/**
 * 
 *
 * @file wh_conf.h
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Fri Apr 25 16:12:11 2014
 *
 **/

typedef struct wh_conf {
  void *dict;
} wh_conf_t;

wh_conf_t*  wh_conf_new();
void        wh_conf_delete(wh_conf_t* conf);

int         wh_conf_load(wh_conf_t* conf, const char* path);

int         wh_conf_get_int(wh_conf_t* conf, const char* key);
const char* wh_conf_get_str(wh_conf_t* conf, const char* key);

#endif /* _WH_CONF_H_ */

/* vim: set expandtab shiftwidth=2 tabstop=2: */
