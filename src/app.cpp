
#include "app.h"
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include "grpc_client/hello_client.h"

using namespace std;

App::App()
{

}

void App::start()
{

}

void App::stop()
{

}

void App::idle()
{
    constexpr int idleTime = 5;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(idleTime));
        std::cout << appName_ << "::idle" << std::endl;
    }
}

void App::setup(const nlohmann::json &cfg)
{
    const auto hello_grpc_addr = cfg["grpc"]["client"]["addr"].get<std::string>();
    grpc_client::HelloWorld::get()->init(hello_grpc_addr);

    hello_server_impl_ = std::make_unique<HelloServer>();
}

void App::run()
{
    BaseApp::run();
    start();
    idle();
}

void App::addGrpcService()
{
    BaseApp::addGrpcService();
    grpcBuilder_.RegisterService(hello_server_impl_.get());
}