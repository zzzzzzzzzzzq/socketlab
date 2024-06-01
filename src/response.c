#include "response.h"

void set_header(char*head,char* name,char* value)
{
    strcat(head,name);
    strcat(head,": ");
    strcat(head,value);
    strcat(head,"\r\n");
    return;
}
char*get_connection(Request r)
{
    int i=0;
    while(r.headers[i].header_name!="Connection")
    {
        i++;
    }
    return r.headers[i].header_value;
}
int response(char*res,Request req)
{
    char path[res_size];
    strcpy(path,"./static_site");
    strcat(path,req.http_uri);
	if(!strcmp(req.http_uri, "/")){
		strcat(path,"index.html");
	}
	struct stat file_buffer;//记录文件状态
	if(stat(path, &file_buffer)){
		return 0;
	}//未找到文件

    char time_buf[res_size]={0};//时间
    time_t now; 
	time(&now); 
	struct tm* Time=localtime(&now); 
	strftime(time_buf,res_size, "%a, %d %b %Y %H:%M:%S %Z", Time);

    char last_modified[res_size]={0};//上次修改时间
    struct tm *t = gmtime(&file_buffer.st_mtime);
	strftime(last_modified,res_size, "%a, %d %b %Y %H:%M:%S %Z",t);

    char content_length[res_size]={0};
	sprintf(content_length, "%ld", file_buffer.st_size);
    char* connection = get_connection(req);
    
    strcpy(res,"HTTP/1.1 200 OK\r\n");
    set_header(res,"Server","liso/1.0");
    set_header(res,"Date",time_buf);
    set_header(res,"Content-Length",content_length);
    set_header(res, "Last-Modified", last_modified);
    set_header(res, "Connection", connection);
    return 1;
}