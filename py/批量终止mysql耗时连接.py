批量终止mysql耗时连接
有时候由于客户端程序或脚本逻辑bug等，会导致有大批的mysql查询，执行很久也不返回，如果情况继续下去，会让mysql服务器变得不可用。这个时候，我们一般会比较简单地杀死执行时间过长的连接，比如大于1000秒。
mysql -uuser_name -pYour_password -hYour_IP -NBA -e 'show processlist' | perl -alne '$F[5] > 1000 and print qq(kill $F[0];)' | mysql -uuser_name -pYour_password -hYour_IP -NBA
