#!/bin/bash
PATH="/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin"

init_check()
{
    ulimit -c unlimited
}
init_check

service_stop()
{
    for((i=1;i<=100;i++))
    do
	pid=$(pgrep -f "\.\/\<your_processor_${i}\>" -d " ")
	if [ -n "$pid" ] ; then
	    kill -12 $pid
	fi

	usleep 200000
	pid=$(pgrep -f "\.\/\<your_processor_${i}\>" -d " ")
	if [ -n "$pid" ] ; then
	    kill -10 $pid
	fi

	cd /usr/local/qqcs/your_path
	rm -f your_processor_${i}.pid
    done
}

service_start() 
{
    cd /usr/local/qqcs/your_path/
    for((i=1;i<100;i++))
    do
		nohup ./your_processor_${1} -c config.ini >/dev/null 2>&1 &
    done
}

case $1 in
    stop)
	echo "SERVICE STOPING......"
	service_stop
	;;
    start)
	echo "SERVICE STARTING......"
	service_start
	;;
    restart)
	echo "SERVICE RESTARTING......"
	service_stop
	service_start
	;;
    *)
	echo "USAGE: $0 { stop | start | restart }"
esac

echo ""
ps -ef | grep "your_processor_" | grep -v grep
echo ""

exit 0