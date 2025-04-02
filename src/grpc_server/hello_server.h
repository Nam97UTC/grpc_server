#ifndef __GRPC_HELLO_SERVER_H__
#define __GRPC_HELLO_SERVER_H__


#include <grpcpp/grpcpp.h>
#include "helloworld.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Logic and data behind the server's behavior.
class HelloServer final : public Greeter::Service {

  public:
    HelloServer() {}
    ~HelloServer() {}

    ::grpc::Status SayHello(ServerContext *context, const HelloRequest *request,
                            HelloReply *reply) override;
};

#endif // __GRPC_HELLO_SERVER_H__
