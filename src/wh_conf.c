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
 * @file wh_conf.c
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Fri Apr 25 17:16:38 2014
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wuhan/wh_conf.h>

#include "dict.h"
#include "fault.h"
#include "hash.h"
#include "utils.h"

#define DICT_INIT_SIZE 2
#define LINE_SIZE      1024
#define KEY_SIZE       256
#define VALUE_SIZE     1024

struct dict_item {
  char* key;
  char* value;
};

static uint64_t str_hash(void* item) {
  struct dict_item* p = (struct dict_item*)item;
  return jenkins_str_hash(p->key);
}

static int str_cmp(void* item1, void* item2) {
  return strcmp(((struct dict_item*)item1)->key,
                ((struct dict_item*)item2)->key);
}

static void* str_alloc(void *tmpl) {
  struct dict_item* item = (struct dict_item*)tmpl;
  struct dict_item* p = (struct dict_item*)malloc(sizeof(struct dict_item));
  if (p == NULL) {
    PANIC("bad alloc");
  }
  int sz = strlen(item->key) + 1;
  p->key = (char*)malloc(sz);
  if (p->key == NULL) {
    PANIC("bad alloc");
  }
  memcpy(p->key, item->key, sz);

  sz = strlen(item->value) + 1;
  p->value = (char*)malloc(sz);
  if (p->value == NULL) {
    PANIC("bad alloc");
  }
  memcpy(p->value, item->value, sz);
  return p;
}

static void str_free(void* item) {
  struct dict_item* p = (struct dict_item*)item;
  free(p->key);
  free(p->value);
  free(p);
}

static char* str_debugstring(void* item) {
  return ((struct dict_item*)item)->key;
}

static dict_func_t conf_dict_func = {.hash  = str_hash,
                                     .cmp   = str_cmp,
                                     .alloc = str_alloc,
                                     .free  = str_free,
                                     .debugstring = str_debugstring};

wh_conf_t* wh_conf_new() {
  dict_t* dict = (dict_t*)dict_new("conf_dict", DICT_INIT_SIZE,
                                   conf_dict_func);
  if (dict == NULL) {
    return NULL;
  }

  wh_conf_t* p = (wh_conf_t*)malloc(sizeof(wh_conf_t));
  if (p == NULL) {
    PANIC("bad alloc");
  }

  p->dict = dict;

  return p;
}

void wh_conf_delete(wh_conf_t* conf) {
  dict_t* dict = (dict_t*)(conf->dict);
  dict_delete(dict);
  free(conf);
}

int wh_conf_load(wh_conf_t* conf, const char* path) {
  int ret = 0;
  FILE* fp = fopen(path, "r");

  if (fp == NULL) {
    PANIC("open conf file failed");
  }

  char* line = (char*)malloc(LINE_SIZE);
  size_t buffn = LINE_SIZE;

  dict_t* dict = (dict_t*)(conf->dict);

  ssize_t n;
  char* key;
  char* value;
  while ((n = getline(&line, &buffn, fp)) != -1) {
    if (line[n - 1] == '\n') {
      line[n - 1] = '\0';
    }

    char* trimmed = trim(line);

    if (trimmed[0] == '#') {
      continue;
    }

    char* delim = strstr(trimmed, "=");
    if (delim == NULL) {
      PANIC("invalid line, no = found: %s", trimmed);
    }

    *delim = '\0';

    key = trim(trimmed);
    value = trim(delim + 1);

    //printf("key: [%s]\n", key);
    //printf("value: [%s]\n", value);

    struct dict_item tmpl;
    tmpl.key = key;
    tmpl.value = value;
    dict_put(dict, &tmpl);

    //dict_debugstring(dict);
  }

  free(line);
  fclose(fp);
  return ret;
}

int wh_conf_get_int(wh_conf_t* conf, const char* key) {
  dict_t* dict = (dict_t*)(conf->dict);
  struct dict_item tmpl;
  tmpl.key = (char*)key;
  struct dict_item* p = (struct dict_item*)dict_get(dict, &tmpl);
  return atoi(p->value);
}

const char* wh_conf_get_str(wh_conf_t* conf, const char* key) {
  dict_t* dict = (dict_t*)(conf->dict);
  struct dict_item tmpl;
  tmpl.key = (char*)key;
  struct dict_item* p = (struct dict_item*)dict_get(dict, &tmpl);
  return p->value;
}

/* vim: set expandtab shiftwidth=2 tabstop=2: */
