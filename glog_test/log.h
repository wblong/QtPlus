#ifndef __LOG_GLOG_H__
#define __LOG_GLOG_H__

#ifdef ERROR
#define GLOG_NO_ABBREVIATED_SEVERITIES
#define ERR             google::GLOG_ERROR
#endif

#include "glog/logging.h"

#include <stdarg.h>

#ifdef MINGW
#else
#include <share.h>
#include <shlobj.h>
#endif

int log_init(const char *argv0, const char *basename, int max_log_size);
void log_finalize(void);
void log_write(int level, char line, const char *fmt, ...);

#ifdef MINGW
#define log_printf(level, fmt, arg...)	    log_write(level, 0, fmt, ##arg)
#define log_printf_line(level, fmt, arg...)	log_write(level, 1, fmt, ##arg)
#else
#ifdef WIN32
#define log_printf(level, fmt, ...)			log_write(level, 0, fmt, __VA_ARGS__)
#define log_printf_line(level, fmt, ...)	log_write(level, 1, fmt, __VA_ARGS__)
#endif
#endif

#define LOG_PRINTF(level, fmt, ...)	do {			    \
	char buf[2048];										\
	sprintf_s(buf, sizeof(buf), fmt, ## __VA_ARGS__);	\
	LOG(level) << buf;									\
} while (0)

#endif
