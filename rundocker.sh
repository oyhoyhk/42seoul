exec_flag=`docker ps -q --filter name=^sandbox$`

if [ -z $exec_flag ] ; then
    docker rmi -f sandbox
    docker build -t sandbox .
    docker run --name sandbox --rm -it -p 6667:6667 sandbox
else
    docker exec -it sandbox /bin/bash
fi
