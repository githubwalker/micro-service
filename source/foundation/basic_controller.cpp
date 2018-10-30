//
//  Created by Ivan Mejia on 12/03/16.
//
// MIT License
//
// Copyright (c) 2016 ivmeroLabs. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include "basic_controller.hpp"
#include "network_utils.hpp"

namespace cfx {
    BasicController::BasicController() {

    }

    BasicController::~BasicController() {

    }

   // how to work with https example has been taken from here
   // https://github.com/Microsoft/cpprestsdk/blob/master/Release/tests/functional/http/listener/listener_construction_tests.cpp
    http_listener_config BasicController::getHttpListenerConfig() const {
        const char * self_signed_cert = R"(
-----BEGIN CERTIFICATE-----
MIIDlzCCAn+gAwIBAgIJAP9ZV+1X94UjMA0GCSqGSIb3DQEBBQUAMGIxCzAJBgNV
BAYTAkNOMQswCQYDVQQIDAJTSDELMAkGA1UEBwwCU0gxEjAQBgNVBAoMCU1JQ1JP
U09GVDERMA8GA1UECwwISFBDLVBBQ0sxEjAQBgNVBAMMCWxvY2FsaG9zdDAeFw0x
NTA4MTkwOTA0MjhaFw00MzAxMDMwOTA0MjhaMGIxCzAJBgNVBAYTAkNOMQswCQYD
VQQIDAJTSDELMAkGA1UEBwwCU0gxEjAQBgNVBAoMCU1JQ1JPU09GVDERMA8GA1UE
CwwISFBDLVBBQ0sxEjAQBgNVBAMMCWxvY2FsaG9zdDCCASIwDQYJKoZIhvcNAQEB
BQADggEPADCCAQoCggEBALLv7AAPa+4wYpa+3tqc9HIHhh8kv/MpV2Dm+oKG27iH
zOugMNAPqLzMAaWCzDRyw27I+jPS3pzAAu6rQ0v2H6XNrie1YEEV27j1WOUS9iFy
vcf6Y+ywUKXvFlN/VM/ZFz9Z8U3jc7Y6unIyoUs8UdX/RRITspb2m7SUxlmLJ+4c
qiLrHwstNB2NHIZN72oc8DaS5eBqBdT9h6NO62RSBTrAlR7Vk9eU/5trYkd5+PoC
pispvU+7Fe24uVerGgU6Yoyd7DMj+3BpbG3g/VkOlGhgH0DNtbKu3v/XOmnzdZn6
dzoOoGFNpG1NeH2Xv0vnvEZP6WG4h/TFSafBJMONNnMCAwEAAaNQME4wHQYDVR0O
BBYEFO1mAjAmLk1J0iT93xfczAE5mxgzMB8GA1UdIwQYMBaAFO1mAjAmLk1J0iT9
3xfczAE5mxgzMAwGA1UdEwQFMAMBAf8wDQYJKoZIhvcNAQEFBQADggEBAFB8AACf
5O+sPe3PZ8IPgwZb+BCXdoXc2rngR/gOaYO019TZyNLuHRzW9FtplzW25IbQ9Jnc
b+jmY2Ill7Zf3TX4OhHEwscJ1G2LBaqZfQlwSbYJmCzvRNSzSbF3RigNQD5Qhdph
vVBdvVGTZnVeatjTOFKUyfhcXf4DMb6eMfaU6il/VJCSMW0j3hYNQjPm3V/PLxnG
fd9T4hpCUd8MK2XG4RqJAzh6x/6v0fc6mRHBS5+qTWYSDGFwITrU1pP2L9qFegpm
aNAom7bdENU8uivd+vrLnG2fKvFSssjVfaXpFLKAICfTJY9A3/CWnZ1AcbE5El7A
adctopihoUrlAb0=
-----END CERTIFICATE-----
)";
        const char * private_key = R"(
-----BEGIN PRIVATE KEY-----
MIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQCy7+wAD2vuMGKW
vt7anPRyB4YfJL/zKVdg5vqChtu4h8zroDDQD6i8zAGlgsw0csNuyPoz0t6cwALu
q0NL9h+lza4ntWBBFdu49VjlEvYhcr3H+mPssFCl7xZTf1TP2Rc/WfFN43O2Orpy
MqFLPFHV/0USE7KW9pu0lMZZiyfuHKoi6x8LLTQdjRyGTe9qHPA2kuXgagXU/Yej
TutkUgU6wJUe1ZPXlP+ba2JHefj6AqYrKb1PuxXtuLlXqxoFOmKMnewzI/twaWxt
4P1ZDpRoYB9AzbWyrt7/1zpp83WZ+nc6DqBhTaRtTXh9l79L57xGT+lhuIf0xUmn
wSTDjTZzAgMBAAECggEAenzd8lScL1qTwlk6ODAE7SHVX/BKLWv5Um4KwdsLAVCE
qC7p+yMdANAtuFzG6Ig+29Fb5KnOlUKjPzmhQZhjpZ4cPzZbg3IxDHV2uqi2L8NZ
wlDWoik3q770a4fYSMd0sHsjQYwXo4CkLJQX8WaDJpgtcehl8g0yHPVSqe0mEkoL
dxdqaZnxprchscxefWaGaysIxEO+V+ZOBaPNf4i8PmBKoMNczWZbLcdKhRL7aLeW
ngPQp1xSWYoN8fPoonpL2qTSop3Nsc2INpwGcYPAj3vxdasC3+DZ8JEJI2AmxpVB
13BLkd3nDzOwimZIlu9Fv+NMJ1vb9XdC249ZOqo68QKBgQDigkws1W429nqDtEtQ
Dr5ebHTdP4gZlNt6vWx5obGLCMBAzoyubfNCCBTCYsCPj8hXxNfiPArPFFkIgEx9
+w0n7BlaYL6SD2xD4q+YzA1/j4Loakxc7N9z8Cyu+/YHifvLhzwqgFnkLfFnVq9N
TF8TatHUYcrbcpawJLz0wr/cnQKBgQDKPAYNTzqPLOOBaE4DfnJNn2zctGU8G5Xp
0L/ED8O1t9AjjV2xVO8PDPNDZAxMzgnIbWeU9iWRSLbr7NloXElKh/QlITjAbSXe
HsUruq1SmDgiaUhEtDaaJ1SqSZZWY2BZqNXMdILOCgvZGnOyyBR2U49zuNaRHyhm
kmZMdIIKTwKBgQDezAk/hEQfvfuuNpZpzcbEu+uLgKVPfFMSfOYJEdnAB0CLvl80
Z6QBzE8XEOmVjHkkk9NBjYuYOsyEhyY2OM2s+hfKBSUOKCt27q+IHRYd5bx+/afV
M41rzc8141ISAlBw1rmAmLVSszojSmmuH7PZNpXkULineCPuaISQQEtWJQKBgQDD
laVsvdEuowUsJEo+ys2VELhiAv1dUnh79u1fmrd2SV085P1WAYRqE+Y4qMvUg/em
JVjmEeBnT+HI7fmdGpOvRyjxt92BDI5w8WVTU2lI1fqEHTpNZ9Te5WbWgfCpf9ax
H74VzCCtT74Bq7l1kFdp0IqOKpcpJu8VtETHcG5LtQKBgQC4Tx7El1Xb4hsI4dvE
h43j3KBb3evlz6vaqgz0BArahYAz2UkkOYDSOPs4K6aOxxXjO0BjqQqCx/tCPcU5
AvLsTlswO+wDLXM1DoKxzFBZL5o8927niqW+vZpzyGc1uPmC1MG7+MDKdZsR+e+9
XzJTD4slrGSJrcpLt/g/Jqqdjg==
-----END PRIVATE KEY-----
)";


        boost::asio::const_buffer cert(self_signed_cert, std::strlen(self_signed_cert));
        boost::asio::const_buffer key(private_key, std::strlen(private_key));

        http_listener_config server_config;
        server_config.set_ssl_context_callback(
            [cert, key](boost::asio::ssl::context& ctx)
            {
                ctx.set_options(boost::asio::ssl::context::default_workarounds);
                ctx.use_certificate_chain(cert);
                ctx.use_private_key(key, boost::asio::ssl::context::pem);
            });

        return std::move(server_config);
    }

    void BasicController::setEndpoint(const std::string & value) {
        uri endpointURI(value);
        uri_builder endpointBuilder;

        endpointBuilder.set_scheme(endpointURI.scheme());
        if (endpointURI.host() == "host_auto_ip4") {
            endpointBuilder.set_host(NetworkUtils::hostIP4());        
        }
        else if (endpointURI.host() == "host_auto_ip6") {
            endpointBuilder.set_host(NetworkUtils::hostIP6());
        }
        endpointBuilder.set_port(endpointURI.port());
        endpointBuilder.set_path(endpointURI.path());

        _listener = http_listener(endpointBuilder.to_uri(), getHttpListenerConfig());
    }

    std::string BasicController::endpoint() const {
        return _listener.uri().to_string();
    }

    pplx::task<void> BasicController::accept() {
        initRestOpHandlers();
        return _listener.open();
    }

    pplx::task<void> BasicController::shutdown() {
        return _listener.close();
    }

    std::vector<utility::string_t> BasicController::requestPath(const http_request & message) {
        auto relativePath = uri::decode(message.relative_uri().path());
        return uri::split_path(relativePath);        
    }
}
