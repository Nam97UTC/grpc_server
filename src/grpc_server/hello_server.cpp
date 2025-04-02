#include "hello_server.h"
#include <iostream>
#include <memory>
#include <string>

::grpc::Status HelloServer::SayHello(ServerContext *context, const HelloRequest *request,
                                HelloReply *reply)
{
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    return Status::OK;
}
