# **第一周**：实现简单的Echo Web Server # 
------
### 具体要求： ###
1. 掌握课本有关HTTP的内容；阅读HTTP/1.1的标准文档RFC2616； 
2. 搭建编程环境（参见“讲解PPT-环境安装配置.pptx）； 
3. 熟悉Socket编程方法； 
4. 掌握lex和yacc正确解析消息（message）的方法； 
5. 实现简单的echo web server。 
    Server 收到 client 的带多请求行的消息后，能够正确解析出来，并且返回响应消息（response message）。分以下3种情况处理：
    * Echo: 如果收到客户端发来的是GET, HEAD和POST方法，则echo回去，即重新封装（encapsulation）消息并返回给客户端。
    * 没实现：如果收到客户端发来的是除GET, HEAD和POST以外的其它方法，服务器并没有实现，则需要返回响应消息“HTTP/1.1 501 Not Implemented\r\n\r\n”。 
    * 格式错误：如果收到的客户端消息的格式错误，应能够识别出来，并返回错误代码为400的HTTP响应消息“HTTP/1.1 400 Bad request\r\n\r\n”。 
7. 使用浏览器测试，能够完成评分细则表中列出的功能。给出测试样例，并将测试结果展示在实验结果部分。 
