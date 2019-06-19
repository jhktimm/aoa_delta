# FROM scratch
FROM ubuntu:xenial
ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && \
    apt-get install -y software-properties-common apt-utils && \
    apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y sudo wget && \
    apt-get install -y g++ cppcheck doxygen cmake make git libboost-all-dev libxml++2.6-dev
    
RUN git clone https://github.com/ChimeraTK/cppext.git && \
    cd cppext && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make -j 3 && \
    sudo make install
        
RUN pwd && \
    git clone https://github.com/ChimeraTK/exprtk-interface.git && \
    cd exprtk-interface && \
    mkdir build && \
    cd build && \
    git submodule init && \
    git submodule update && \
    cmake .. && \
    make -j 3 && \
    make install && \
    pwd
    
RUN pwd && \
    git clone https://github.com/ChimeraTK/DeviceAccess.git && \
    cd DeviceAccess && \
    mkdir build && \
    cd build && \
    cmake .. && \    
    nice make -j 3 
    
RUN cd DeviceAccess/build && \
    make install; exit 0 $$ \
    pwd

RUN git clone https://github.com/ChimeraTK/ControlSystemAdapter.git && \
    cd ControlSystemAdapter && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make -j 3 && \
    make install

# DOOCS    
RUN wget -O - http://doocs.desy.de/pub/doocs/DOOCS-key.gpg.asc | sudo apt-key add - && \
    sh -c 'echo "deb http://doocs.desy.de/pub/doocs `lsb_release -sc` main" > /etc/apt/sources.list.d/doocs.list' && \
    apt update && \
    apt install -y dev-doocs-clientlib dev-doocs-serverlib dev-doocs-libgul
    
RUN git clone https://github.com/ChimeraTK/DoocsServerTestHelper.git && \
    cd DoocsServerTestHelper && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make -j 3 && \
    make install  
    
RUN git clone https://github.com/ChimeraTK/ControlSystemAdapter-DoocsAdapter.git && \
    cd ControlSystemAdapter-DoocsAdapter && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make -j 3 && \
    make install
    
RUN git clone https://github.com/ChimeraTK/ApplicationCore.git && \
    apt install -y libhdf5-dev && \
    cd ApplicationCore && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make -j 3 && \
    make install

RUN git clone https://github.com/ChimeraTK/DeviceAccess-DoocsBackend.git && \
    cd DeviceAccess-DoocsBackend && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make -j 3 && \
    make install    
        
RUN git clone https://github.com/jhktimm/aoa_delta.git && \
    apt install -y libjsoncpp-dev && \
    apt install -y dev-doocs-eqdaqdatalib dev-doocs-lzo2lib dev-doocs-ttf2xmllib dev-doocs-daqbmlib dev-doocs-daqreaderlib && \
    cd aoa_delta && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make -j 3 && \
#     mkdir /daq_data && \
#     mkdir /daq_data/xfel && \
#     mkdir /daq_data/xfel/USR1 && \
    cd /aoa_delta/workdir
    
#RUN apt-get install -y rpcbind

# Start rpcbind at launch of the container, required for DOOCS
#ENTRYPOINT ["bash", "-c", "rpcbind -w; /bin/bash"]

ENV TZ=CET
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
WORKDIR /space/aoa_delta/workdir

RUN apt install -y openssh-client openssh-server sshfs && ssh-keygen -A && \
	sed -i 's/required\(.*pam_loginuid\)/optional\1/' /etc/pam.d/sshd

