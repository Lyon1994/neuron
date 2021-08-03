/**
 * NEURON IIoT System for Industry 4.0
 * Copyright (C) 2020-2021 EMQ Technologies Co., Ltd All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 **/

#ifndef NEURON_LOG_H
#define NEURON_LOG_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define LOG_VERSION "0.1.0"

typedef struct {
    va_list     ap;
    const char *fmt;
    const char *file;
    const char *func;
    struct tm * time;
    void *      udata;
    int         line;
    int         level;
} log_Event;

typedef void (*log_LogFn)(log_Event *ev);
typedef void (*log_LockFn)(bool lock, void *udata);

enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };

extern const char *log_level_string(int level);
extern void        log_set_lock(log_LockFn fn, void *udata);
extern void        log_set_level(int level);
extern void        log_set_quiet(bool enable);
extern int         log_add_callback(log_LogFn fn, void *udata, int level);
extern int         log_add_fp(FILE *fp, int level);
extern void log_log(int level, const char *file, int line, const char *func,
                    const char *fmt, ...);

/*
#define fatal(msg, rv)                             \
    {                                              \
        log_fatal("%s:%s", msg, strerror(rv)); \
        exit(1);                                   \
    }
*/

#define log_trace(...) \
    log_log(LOG_TRACE, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define log_debug(...) \
    log_log(LOG_DEBUG, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define log_info(...) \
    log_log(LOG_INFO, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define log_warn(...) \
    log_log(LOG_WARN, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define log_error(...) \
    log_log(LOG_ERROR, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define log_fatal(...) \
    log_log(LOG_FATAL, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

#endif
