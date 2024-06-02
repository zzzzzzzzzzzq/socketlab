#include "response.h"

void set_header(char *head, char *name, char *value)
{
    strcat(head, name);
    strcat(head, ": ");
    strcat(head, value);
    strcat(head, "\r\n");
    return;
}
char *get_connection(Request r)
{
    int i = 0;
    while (strcmp(r.headers[i].header_name, "Connection"))
    {
        i++;
    }
    return r.headers[i].header_value;
}
char *get_file_type(char *path)
{
    char *result = (char *)malloc(sizeof(char *) * 100);
    size_t len = strlen(path);
    int i;
    char extension[100] = {0};
    for (i = len - 1; i >= 0 && len - i < 100; i--)
    {
        int c_len = len - i;
        if (path[i] == '.')
        {
            strncpy(extension, path + len - c_len + 1, c_len - 1);
            break;
        }
    }
    if (!strlen(extension))
    {
        strcpy(result, "application/octet-stream");
        return result;
    }
    for (i = 0; extension[i]; i++)
    {
        extension[i] = tolower(extension[i]);
    }
    switch (get_TYPE(extension))
    {
    case HTML:
        // In case we use Chinese, UTF-8 is strictly needed.
        strcpy(result, "text/html; charset=utf-8");
        return result;
    case CSS:
        strcpy(result, "text/css");
        return result;
    case PNG:
        strcpy(result, "image/png");
        return result;
    case JPEG:
        strcpy(result, "image/jpeg");
        return result;
    case GIF:
        strcpy(result, "image/gif");
        return result;
    case ICO:
        strcpy(result, "image/ico");
        return result;
    default:
        strcpy(result, "application/octet-stream");
        return result;
    }
}
// Get File TYPE
int get_TYPE(char *extension)
{
    if (!strcmp(extension, "html") || !strcmp(extension, "text/html"))
    {
        return HTML;
    }
    else if (!strcmp(extension, "css") || !strcmp(extension, "text/css"))
    {
        return CSS;
    }
    else if (!strcmp(extension, "png") || !strcmp(extension, "image/png"))
    {
        return PNG;
    }
    else if (!strcmp(extension, "jpeg") || !strcmp(extension, "image/jpeg"))
    {
        return JPEG;
    }
    else if (!strcmp(extension, "gif") || !strcmp(extension, "image/gif"))
    {
        return GIF;
    }
    else if (!strcmp(extension, "ico") || !strcmp(extension, "image/ico"))
    {
        return ICO;
    }
    else
    {
        return NONE;
    }
}
int response(char *res, Request req)
{
    char path[res_size];
    strcpy(path, "./static_site");
    strcat(path, req.http_uri);
    if (!strcmp(req.http_uri, "/"))
    {
        strcat(path, "index.html");
    }
    struct stat file_buffer;      // 记录文件状态
    if (stat(path, &file_buffer)) // 成功返回0 else -1
    {
        return 0;
    } // 未找到文件

    char time_buf[res_size] = {0}; // 时间
    time_t now;
    time(&now);
    struct tm *Time = localtime(&now);
    strftime(time_buf, res_size, "%a, %d %b %Y %H:%M:%S %Z", Time);

    char last_modified[res_size] = {0}; // 上次修改时间
    struct tm *t = gmtime(&file_buffer.st_mtime);
    strftime(last_modified, res_size, "%a, %d %b %Y %H:%M:%S %Z", t);

    char content_length[res_size] = {0};
    sprintf(content_length, "%ld", file_buffer.st_size);
    char *connection = get_connection(req);
    char *content_type = get_file_type(path);

    strcpy(res, "HTTP/1.1 200 OK\r\n");
    set_header(res, "Server", "liso/1.0");
    set_header(res, "Date", time_buf);
    set_header(res, "Content-Length", content_length);
    set_header(res, "Content-type", content_type);
    set_header(res, "Last-Modified", last_modified);
    set_header(res, "Connection", connection);
    strcat(res, "\r\n");
    if (strcmp(req.http_method, "GET") == 0)
    {
        int fd_in = 0;
        if ((fd_in = open(path, O_RDONLY)) < 0)
        {
            return 0;
        }
        struct stat file_stat;
        if ((fstat(fd_in, &file_stat)) < 0)
        {
            return 0;
        }
        size_t file_len = file_stat.st_size;
        if (file_len <= 0)
        {
            close(fd_in);
            return 0;
        }
        char *file = mmap(0, file_len, PROT_READ, MAP_PRIVATE, fd_in, 0);
        if (file == MAP_FAILED)
        {
            close(fd_in);
            return 0;
        }
        strcat(res, file);
        strcat(res, "\r\n");
        munmap(file, file_len);
        close(fd_in);
    }
    return 1;
}