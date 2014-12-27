#!/usr/bin/python
# -*- coding: utf-8 -*-
import MySQLdb
import re

#create connection
con= MySQLdb.connect(host="localhost", user="root", passwd="", db="test")

#正则匹配手机号码
#国内目前的手机号码都是11位数字，三大运营商的号码段基本都在上面列出来了，
#我们这里除了147的号码的段，其他的都只考虑前两位，
#第三位就不考虑了，否则，工作量也很大。前两位包括13*、15*、18*。
p = re.compile('^1[358]\d{9}$|^147\d{8}')

with con:
    #create a cursor
    cursor = con.cursor();
    query = "SELECT * FROM sqlcmd"
    cursor.execute(query)    
    rows = cursor.fetchall()              #fetchall() fetchone()
    
    #for i in range(cursor.rowcount):
    for row in rows:
        #row = cursor.fetchone()
        print "%d, %s, %s" %(row[0], row[1], row[2])
        match = p.match(row[1])

        if match:
            #print match.group()
            updateSql = "update sqlcmd set sqlstr='%s' where id=%d" % (row[1], row[0])
            cursor.execute(updateSql)
