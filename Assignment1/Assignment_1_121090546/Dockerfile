FROM --platform=amd64 ubuntu:20.04
WORKDIR /app
ADD . .
USER root
RUN sed -i "s@http://.*archive.ubuntu.com@http://mirrors.ustc.edu.cn@g" /etc/apt/sources.list\
    && sed -i "s@http://.*security.ubuntu.com@http://mirrors.ustc.edu.cn@g" /etc/apt/sources.list\
    && apt update -y
RUN apt upgrade -y
RUN apt purge cmake -y
RUN apt install -y gcc\
    && apt install -y g++\
    && apt install -y libssl-dev\
    && apt install -y clang\
    && apt install -y make\
    && apt install -y ninja-build\
    && apt install -y iverilog\
    && apt install -y gdb\
    && apt install -y wget\
    && apt install -y tar
# cmake 3.19.2
WORKDIR /root
RUN wget https://github.com/Kitware/CMake/releases/download/v3.19.2/cmake-3.19.2.tar.gz --no-check-certificate
RUN tar -xzvf cmake-3.19.2.tar.gz
WORKDIR /root/cmake-3.19.2
RUN ./bootstrap --prefix=/usr/local/cmake-3.19.2
RUN make -j 16
RUN make
RUN make install

WORKDIR /app
ENV PATH=/usr/local/cmake-3.19.2/bin:${PATH}
RUN cmake -DCMAKE_BUILD_TYPE=Debug .
CMD [ "/bin/bash", "-c", "gdb", "./assignment1" ]