
#include "hello_client.h"
#include <string>

using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

namespace grpc_client
{
HelloWorld *HelloWorld::instance = nullptr;

void HelloWorld::init(const std::string &addr) {
    address_ = addr;
    ChannelArguments args;
    args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, 10000);
    args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 10000);

    std::cout <<"grpc client connect to  uri=" << address_ << std::endl;
}

std::string HelloWorld::SayHello(const std::string& user)
{
    HelloRequest request;
    request.set_name(user);

    HelloReply reply;

    grpc::ClientContext context;
    ChannelArguments args;
    auto stub = Greeter::NewStub(
        grpc::CreateCustomChannel(address_, grpc::InsecureChannelCredentials(), args));
    ::grpc::Status status = stub->SayHello(&context, request, &reply);
    
    if (status.ok()) {
        return reply.message();
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message()
                    << std::endl;
        return "RPC failed";
    }
}

} // namespace grpc_client

grpc_client::HelloWorld *HelloWorldInstance()
{
    return grpc_client::HelloWorld::get();
}
