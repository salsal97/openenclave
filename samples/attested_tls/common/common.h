// Copyright (c) Open Enclave SDK contributors.
// Licensed under the MIT License.
//
#define ADD_TEST_CHECKING

// Following flag modifies behavior of the test to make it
// suitable for scenario where the server is deployed in some
// sort of replicated set and is accessed via a load balancer.
// The flag modifies the behavior in two ways:
// 1. Handle load balancer pings: load balancer pings fail the tls
// handshake with an EOF error. Enabling the flag ignores this error
// and also squelches logs if this has been
// 2. Makes the server run in a loop for availability.
//#define CLOUD_DEPLOYMENT

#define TLS_CLIENT "TLS client:"
#define TLS_SERVER "TLS server:"

#define CLIENT_PAYLOAD "GET / HTTP/1.0\r\n\r\n"
#define SERVER_PAYLOAD                                   \
    "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n" \
    "<h2>mbed TLS Test Server</h2>\r\n"                  \
    "<p>Successful connection : </p>\r\n"                \
    "A message from TLS server inside enclave\r\n"

#define CLIENT_PAYLOAD_SIZE strlen(CLIENT_PAYLOAD)
#define SERVER_PAYLOAD_SIZE strlen(SERVER_PAYLOAD)
