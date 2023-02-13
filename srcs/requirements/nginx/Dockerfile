FROM	debian:buster

RUN		apt-get update
RUN		apt-get install -y nginx \
                openssl

RUN mkdir /etc/nginx/ssl
RUN openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes \
       -out /etc/nginx/ssl/yooh.crt \
       -keyout /etc/nginx/ssl/yooh.key \
       -subj "/C=KO/ST=Seoul/L=Seoul/O=42 School/OU=yooh/CN=yooh/"

COPY ./conf/nginx.conf /etc/nginx/conf.d

RUN mkdir -p /run/nginx

EXPOSE	443

CMD ["nginx", "-g", "daemon off;"]