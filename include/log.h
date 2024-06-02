#ifndef LOG_H
#define LOG_H

void log_request(const char *client_ip, const char *request_line, int status_code, size_t response_size);

#endif // LOG_H
