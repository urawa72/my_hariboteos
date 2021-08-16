FROM alpine:3.10

ENV IMAGE_NAME=haribote-os

RUN apk update && \
    apk --no-cache add \
        build-base \
        nasm \
        mtools

WORKDIR /haribos

CMD ["/bin/ash"]
