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
 * @file wh_log.c
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Fri May  9 17:30:07 2014
 *
 **/

#include <stdio.h>
#include <stdint.h>

#include <wuhan/wh_log.h>

#include "utils.h"

__thread char   t_errno_buff[512];
__thread char   t_time_buff[32];
__thread time_t t_last_second;

enum wh_log_level g_log_level = DEBUG;

const char* g_log_level_name[NUM_LOG_LEVELS] = {
  "TRACE",
  "DEBUG",
  "INFO",
  "WARN",
  "ERROR",
  "FATAL",
};

/* vim: set expandtab shiftwidth=2 tabstop=2: */
