/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2014, Menglong TAN <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _LT_FAULT_H_
#define _LT_FAULT_H_

/**
 * 
 *
 * @file fault.h
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Mon Apr 21 15:33:08 2014
 *
 **/

#include <stdio.h>
#include <stdarg.h>

#define PANIC(fmt, args...)                           \
  do {                                                \
    fprintf(stderr, "[%s:%s:%d] panic: " fmt "\n",    \
            __FILE__, __FUNCTION__, __LINE__,         \
            ##args);                                  \
    exit(-1);                                         \
  } while(0)

#define CRY(fmt, args...)                            \
  do {                                               \
    fprintf(stderr, "[%s:%s:%d] cry: " fmt "\n",     \
            __FILE__, __FUNCTION__, __LINE__,        \
            ##args);                                 \
  } while(0)

#endif /* _LT_FAULT_H_ */

/* vim: set expandtab shiftwidth=2 tabstop=2: */
