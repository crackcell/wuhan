/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2014, Menglong TAN <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _WH_LOG_H_
#define _WH_LOG_H_

/**
 * 
 *
 * @file wh_log.h
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Fri May  9 17:21:33 2014
 *
 **/

enum wh_log_level {
  TRACE,
  DEBUG,
  INFO,
  WARN,
  ERROR,
  FATAL,
  NUM_LOG_LEVELS,
};

typedef struct wh_log {
  enum wh_log_level log_level;
} wh_log_t;

void wh_log_set_level(enum wh_log_level level);

#endif /* _WH_LOG_H_ */

/* vim: set expandtab shiftwidth=2 tabstop=2: */
