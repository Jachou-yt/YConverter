FROM ubuntu:latest
LABEL authors="matisse"

ENTRYPOINT ["top", "-b"]