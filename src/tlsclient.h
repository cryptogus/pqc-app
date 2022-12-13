#pragma once

#include "client.h"
#include "tcpclient.h"
#include "tlssession.h"

struct TlsClient : public Client, public TlsSession {
	TcpClient tcpClient_;
    STACK_OF(OPENSSL_STRING) *ssl_args_ = nullptr; //groups flag, kem alg id
    SSL_CONF_CTX *cctx_{nullptr};
    SSL_CTX *ctx_{nullptr};
    static int config_ctx(SSL_CONF_CTX *cctx, STACK_OF(OPENSSL_STRING) *str, SSL_CTX *ctx);

    bool connect(Ip ip, int port) override;
};
