#ifndef __MODULES_OBEJCTS_KDBLOG_H__
#define __MODULES_OBEJCTS_KDBLOG_H__

#include "stdarg.h"


#define KDB_LOG_VALID false

#if KDB_LOG_VALID

inline int32_t GetVarArgs(char* Dest, int32_t DestSize, const char* Fmt, ...) {
	va_list ap;
	va_start(ap, Fmt);
	int32_t result = vsnprintf(Dest, DestSize, Fmt, ap);
	va_end(ap);

	return result;
}

#define LOG_BUFFER_LEN 512
static char stackBuffer[LOG_BUFFER_LEN];

#define KDB_LOG(Format, ...) {\
	if (KDB_LOG_VALID) { \
		const char* logString = Format; \
		char* logBuffer = nullptr; \
		logBuffer = stackBuffer; \
		int32_t result = GetVarArgs(logBuffer, LOG_BUFFER_LEN, logString, ##__VA_ARGS__); \
		logBuffer[result] = '\n'; \
		logBuffer[result + 1] = 0; \
		printf(logBuffer, ##__VA_ARGS__); \
	} \
} \

#else //KDB_LOG_VALID

#define KDB_LOG(Format, ...) ;

#endif //KDB_LOG_VALID

#endif // __MODULES_OBEJCTS_KDBLOG_H__