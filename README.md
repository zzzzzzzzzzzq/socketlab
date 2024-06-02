# **第二周**：实现HEAD、GET和POST方法 #
------
### 具体要求： ###
1. 完善服务器的功能，使其能够正确响应HTTP1.1请求消息，并按照RFC 2616
中的定义实现HEAD、GET和POST的持久连接（persistent connection）[5]。 
    *如果收到客户端发来的 GET, HEAD 和 POST 方法，服务器按照RFC2616 的规定进行处理并发回响应消息。 
    *支持4种HTTP 1.1 出错代码：400，404，501，505。能够准确判别客户端消息，并发回响应消息。 
    *妥善管理接收缓冲区，避免由于客户端请求消息太长导致的缓冲区溢出问题。 
2. 服务器能够处理读写磁盘文件时遇到的错误（例如，权限、文件不存在、IO错误等）。 
3. 创建简化的日志记录模块，记录格式化日志。 
    使用日志记录程序运行的过程，方便调试和追踪。可以参考Apache 的日志文件。 
    *按照Apache日志文件中“Error Log”的格式记录服务器的出错情况； 
    *按照Apache日志文件中“Access Log”的“Common Log Format”记录服务器处理的请求； 
    *可以创建其它方便调试的日志（只是为了方便调试，不做格式要求，不作为得分点）。 
4. 不需要实现分块（Chunking）。 
5. 不需要实现Conditional GETs。 
6. 响应的要求 
    *对GET/HEAD请求发回的响应必须包含"HTTP/1.1 200 OK\r\n"。 
    *GET 方法获取的网页使用基础代码提供的默认网页，网页位于“/webServerStartCodes-new/static_site/index.html”。 
    *400、404、501、505 的响应为 
    RESPONSE_400 = "HTTP/1.1 400 Bad request\r\n\r\n" 
    RESPONSE_404 = "HTTP/1.1 404 Not Found\r\n\r\n" 
    RESPONSE_501 = "HTTP/1.1 501 Not Implemented\r\n\r\n" 
    RESPONSE_505 = "HTTP/1.1 505 HTTP Version not supported\r\n\r\n" 
