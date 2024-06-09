# **第三周**：实现HTTP的并发请求 #
------
### 具体要求： ###
1. 服务器能连续响应客户端使用同一个TCP连接同时发送的多个请求GET/HEAD/POST，即支持HTTP pipelining[6]。 
2. 服务器按照RFC2616规定的顺序处理HTTP的并发请求。 
3. 对于HTTP的并发请求，如果服务器认为其中一个请求是错误的并拒绝该请求，那么服务器需要能够正确识别并解析出并发到达的下一条请求。
