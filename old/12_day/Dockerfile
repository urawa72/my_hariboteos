FROM ubuntu:20.04

RUN apt update && \
  apt install -y \
	  build-essential \
	  gcc-7 \
		mtools \
		nasm

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 7 && \
  update-alternatives --config gcc

WORKDIR /haribos

CMD ["/bin/bash"]
