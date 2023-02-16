#!/bin/sh

mysql_install_db

/etc/init.d/mysql start

if [ -d "/var/lib/mysql/$MYSQL_DATABASE" ]
then 

	echo "Database already exists"
else


mysql  -uroot << _EOF_

UPDATE mysql.user SET Password='${MARIADB_ROOT_PASSWORD}' WHERE User='root';

USE mysql;

ALTER USER 'root'@'localhost' IDENTIFIED BY '${MARIADB_ROOT_PASSWORD}';

FLUSH PRIVILEGES;

CREATE DATABASE IF NOT EXISTS ${MARIADB_DATABASE};

USE ${MARIADB_DATABASE};

CREATE USER ${MARIADB_USER}@'%';

GRANT ALL PRIVILEGES ON ${MARIADB_DATABASE}.* TO ${MARIADB_USER}@'%' IDENTIFIED BY '${MARIADB_PASSWORD}';

FLUSH PRIVILEGES;

_EOF_

mysql -uroot -p$MYSQL_ROOT_PASSWORD $MYSQL_DATABASE < /usr/local/bin/wordpress.sql

fi

/etc/init.d/mysql stop

exec "$@"