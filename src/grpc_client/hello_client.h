#ifndef __SERVICE_HELLO_CLIENT_H__
#define __SERVICE_HELLO_CLIENT_H__

#include "helloworld.grpc.pb.h"
#include "helloworld.pb.h"
#include <grpcpp/grpcpp.h>
#include <memory>
#include <thread>

using grpc::Channel;
using grpc::ChannelArguments;
using grpc::ClientAsyncReaderWriter;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

namespace grpc_client {

class HelloWorld {

  public:
    HelloWorld(){};
    HelloWorld(const HelloWorld &) = delete;
    HelloWorld &operator=(const HelloWorld &) = delete;
    HelloWorld(HelloWorld &&) = delete;
    HelloWorld &operator=(HelloWorld &&) = delete;

    void init(const std::string &addr);
    static HelloWorld *get() {
        if (!instance) {
            instance = new HelloWorld();
        }
        return instance;
    }

    std::string SayHello(const std::string& user);

  private:
    ChannelArguments args_;
    std::string address_;
    static HelloWorld *instance;
};

}

grpc_client::HelloWorld *HelloWorldInstance();

#endif // __SERVICE_HELLO_CLIENT_H__
