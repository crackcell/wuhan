/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2014, Menglong TAN <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _HASH_H_
#define _HASH_H_

/**
 * 
 *
 * @file hash.h
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Fri Apr 25 18:23:34 2014
 *
 **/

#include <stdint.h>

// Jenkins' One-at-a-Time hash for strings
inline uint32_t jenkins_str_hash(const char* s) {
  uint32_t hash = 0;

  for(; *s; ++s)
  {
    hash += *s;
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);

  return hash;
}

#endif /* _HASH_H_ */

/* vim: set expandtab shiftwidth=2 tabstop=2: */
