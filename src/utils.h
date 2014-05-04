/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2014, Menglong TAN <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

/**
 * 
 *
 * @file util.h
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Fri Apr 25 21:57:43 2014
 *
 **/

#include <string.h>
#include <ctype.h>

char* trim(char* str) {
  char *end;

  // Trim leading space
  while(isspace(*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}

#endif /* _UTIL_H_ */

/* vim: set expandtab shiftwidth=2 tabstop=2: */
