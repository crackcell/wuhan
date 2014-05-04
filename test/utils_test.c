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
#include <utils.h>

int main(int argc, char *argv[]) {
  char line[] = "  this is a test  ";
  char* p = trim(line);
  printf("[%s]\n", p);
  return 0;
}

/* vim: set expandtab shiftwidth=2 tabstop=2: */
