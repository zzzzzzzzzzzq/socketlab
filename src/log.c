#include <stdio.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
#include "log.h"

#define LOG_FILE "access.log"

// 获取当前时间字符串
void get_current_time(char *buffer, size_t size)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%d/%b/%Y:%H:%M:%S %z", t);
}

// 记录日志
void log_request(const char *client_ip, const char *request_line, int status_code, size_t response_size)
{
    char time_str[64];
    get_current_time(time_str, sizeof(time_str));

    FILE *log_file = fopen(LOG_FILE, "a");
    if (log_file == NULL)
    {
        perror("Failed to open log file");
        return;
    }

    fprintf(log_file, "%s - - [%s] \"%s\" %d %zu\n",
            client_ip, time_str, request_line, status_code, response_size);

    fclose(log_file);
}
