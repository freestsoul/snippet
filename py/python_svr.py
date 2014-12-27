#!/usr/bin/python
# -*- coding: utf-8 -*-
from socket import socket

s = socket()
#需要传输的数据
data = {'PROGRAM':'test', 'CMD':'QUERY', 'UIN':'492056364'}

# 将字典型数据打包成字符串格式
# 这里用到了列表推导式语法和字符串格式化
content = '&'.join(['%s=%s' %item for item in data.items()])
print "%s" %content

# 再加上通用的LEN部分，内置函数len返回字符串/列表等对象的元素个数
real_content = 'LEN=%05d&%s' % (len(content), content)
print "%s" % real_content

addr = ('172.23.1.105', 17857)
s.content(addr)

#发送数据, 返回实际发送的数据长度
s.send(real_content)


