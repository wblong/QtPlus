
#include "log.h"

#ifdef ERROR
/* avoid wingdi.h repeat defined ERROR */
#define INFO            google::GLOG_INFO
#define WARNING         google::GLOG_WARNING
#define ERR             google::GLOG_ERROR
#define FATAL           google::GLOG_FATAL
#endif

int log_init(const char *argv0, const char *basename, int max_log_size)
{
    //初始化glog
    google::InitGoogleLogging(argv0);
    //初始化glog输出
    google::SetLogDestination(google::GLOG_INFO, basename);
    //设置输出级别到错误窗口
    google::SetStderrLogging(google::GLOG_INFO);
    FLAGS_colorlogtostderr = true;
    //日志文件的最大值max_log_size
    FLAGS_max_log_size = max_log_size;
    //如果磁盘写满是否停止日志记录
    FLAGS_stop_logging_if_full_disk = true;
    return 0;
}

void log_finalize(void)
{
}

void log_write(int level, char line, const char *fmt, ...)
{
	#define buffer_size	2048
    //va_list;va_start;va_end;va_arg
	va_list ap;
	char buffer[buffer_size + 3];
	unsigned int size;

	va_start(ap, fmt);
	size = vsnprintf_s(buffer, buffer_size, buffer_size, fmt, ap);
	if (line) {
		buffer[size] = '\r';
		buffer[size + 1] = '\n';
		buffer[size + 2] = '\0';
	}
	va_end(ap);

    switch (level) {
    case INFO:
        LOG(INFO) << buffer;
        break;
    case WARNING:
        LOG(WARNING) << buffer;
        break;
    case ERR:
        LOG(ERROR) << buffer;
        break;
    case FATAL:
        LOG(FATAL) << buffer;
        break;
    default:
        LOG(INFO) << buffer;
        break;
    }
}