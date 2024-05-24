#include "parse.h"

/**
* Given a char buffer returns the parsed request headers
*/
Request * parse(char *buffer, int size, int socketFd) {
  //Differant states in the state machine
	enum {
		STATE_START = 0, STATE_CR, STATE_CRLF, STATE_CRLFCR, STATE_CRLFCRLF
	};

	int i = 0, state;
	int header_size=0;//记录请求行个数
	size_t offset = 0;
	char ch;
	char buf[8192];
	memset(buf, 0, 8192);

	state = STATE_START;
	while (state != STATE_CRLFCRLF) {
		char expected = 0;

		if (i == size)
			break;

		ch = buffer[i++];
		buf[offset++] = ch;

		switch (state) {
		case STATE_START:
		case STATE_CRLF:
			expected = '\r';
			break;
		case STATE_CR:
		case STATE_CRLFCR:
			expected = '\n';
			break;
		default:
			state = STATE_START;
			continue;
		}

		if (ch == expected)
			state++;
		else
			state = STATE_START;

	}
	if(state==STATE_CR)header_size++;//每次换行更新请求行数量
    //Valid End State
	if (state == STATE_CRLFCRLF) {
		Request *request = (Request *) malloc(sizeof(Request));
        request->header_count=0;
        //TODO You will need to handle resizing this in parser.y
        request->headers = (Request_header *) malloc(sizeof(Request_header)*header_size);
		set_parsing_options(buf, i, request);

		if (yyparse() == SUCCESS) {
            return request;
		}
	}
    //TODO Handle Malformed Requests
    printf("Parsing Failed\n");
	return NULL;
}
int getcode(char *text,int r,int f)
{
 Request *request = parse(text, r, f);
if(request==NULL){
	return 400;
	} 
  if(strcmp(request->http_method,"GET")!=0&&strcmp(request->http_method,"POST")!=0&&strcmp(request->http_method,"HEAD")!=0){
    free(request->headers);
    free(request);
    return 501;
  }//没实现
  free(request->headers);
  free(request);
  return 200;
}
