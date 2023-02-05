FROM ubuntu

RUN	apt update && apt upgrade
RUN apt	install -y inspircd
RUN apt install -y tcpflow
RUN apt install -y irssi
RUN mkdir /var/run/inspircd
RUN echo "alias myserver='inspircd --runasroot --nofork'" >> ~/.bashrc
RUN echo "alias myclient='irssi -c localhost -p 6667'" >> ~/.bashrc
RUN echo "alias mytcp='tcpflow -i lo'" >> ~/.bashrc

EXPOSE 6667

CMD ["/bin/bash"]
