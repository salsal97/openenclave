FROM ubuntu:18.04 as openenclave
LABEL stage=openenclave

RUN apt update; apt-get -yqq install git ssh make

RUN mkdir -p -m 0600 ~/.ssh && ssh-keyscan github.com >> ~/.ssh/known_hosts

## Install tools required to install openenclave
RUN apt update; apt -y install wget gnupg python apt-transport-https libssl1.0.0 libssl-dev git

## Adding the Intel and Microsoft repositories to apt
RUN echo 'deb [arch=amd64] https://download.01.org/intel-sgx/sgx_repo/ubuntu bionic main' | tee /etc/apt/sources.list.d/intel-sgx.list \
    && wget -qO - https://download.01.org/intel-sgx/sgx_repo/ubuntu/intel-sgx-deb.key | apt-key add -
RUN echo "deb [arch=amd64] https://packages.microsoft.com/ubuntu/18.04/prod bionic main" | tee /etc/apt/sources.list.d/msprod.list \
    && wget -qO - https://packages.microsoft.com/keys/microsoft.asc | apt-key add -

## Install openenclave & openenclave platform software (psw)
RUN apt update \
    && apt -y install libsgx-enclave-common libsgx-enclave-common-dev libsgx-dcap-ql libsgx-dcap-ql-dev az-dcap-client open-enclave gcc g++


RUN git clone --single-branch --branch vtikoo/attested-tls-k8s https://github.com/salsal97/openenclave.git

WORKDIR /openenclave/samples/attested_tls

RUN . /opt/openenclave/share/openenclave/openenclaverc \
    && export CC=gcc && export CXX=g++ && export PKG_CONFIG_PATH=/opt/openenclave/share/pkgconfig/ \
    && make

CMD make run


# FROM ubuntu:18.04

# ## Install openenclave & openenclave platform software (psw)
# RUN apt update \
#     && apt -y install libsgx-enclave-common libsgx-enclave-common-dev libsgx-dcap-ql libsgx-dcap-ql-dev az-dcap-client open-enclave gcc g++

# COPY --from=openenclave /openenclave/samples samples/
# WORKDIR /samples/attested_tls

# COPY --from=openenclave /openenclave/samples/attested_tls/server server/
# COPY --from=openenclave /openenclave/samples/attested_tls/client client/
# COPY --from=openenclave /openenclave/samples/attested_tls/non_enc_client non_enc_client/

# COPY --from=openenclave /openenclave/samples/attested_tls/server/host/tls_server_host .
# COPY --from=openenclave /openenclave/samples/attested_tls/server/enc/tls_server_enc.signed .

# COPY --from=openenclave /openenclave/samples/attested_tls/client/host/tls_client_host .
# COPY --from=openenclave /openenclave/samples/attested_tls/client/enc/tls_client_enclave.signed .

# COPY --from=openenclave /openenclave/samples/attested_tls/non_enc_client/tls_non_enc_client .

# RUN ls server/

# RUN ls client/ 

# RUN ls non_enc_client/