#include "base_app.h"
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <execinfo.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <set>
#include <signal.h>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;

void BaseApp::handleSIGSEGV(int sig) {
    signal(sig, SIG_DFL);
    kill(getpid(), sig);
}

void BaseApp::handleSIGINT(int sig __attribute__((unused))) {
    cout << __func__ << endl;
    exit(0);
}

void BaseApp::readConfiguration(nlohmann::json &appCfg) {
    try {
        ifstream appConfigFile(string("/home/oem/work_space/grpc_server/assets/app.json").c_str());
        if (appConfigFile.ios::eof()) {
            throw runtime_error("Config file is empty");
        }

        // Make sure the config is open
        if (!appConfigFile.is_open()) {
            throw runtime_error("Can't open app config");
        }

        appConfigFile >> appCfg;

    } catch (exception &e) {
        throw string(e.what());

    } catch (...) {
        throw "Can't open config";
    }
}

void BaseApp::handleConfigUpdate()
{
    readConfiguration(appCfg_);
}

void BaseApp::configThread()
{
    while (true) {
        try {
            this_thread::sleep_for(chrono::seconds(10));
            handleConfigUpdate();
        } catch (...) {
        }
    }
}


void BaseApp::startConfigThread()
{
    thread t = thread([this] { configThread(); });
    t.detach();
}

void BaseApp::startServer()
{
    thread t = thread([this] {
        auto grpcAddr = appCfg_["grpc"]["server"]["addr"].get<std::string>();

        grpcBuilder_.AddListeningPort(grpcAddr, grpc::InsecureServerCredentials());

        addGrpcService();

        std::cout << "grpc server at: " << grpcAddr << std::endl;
        rpcServer_ = grpcBuilder_.BuildAndStart();
    });

    t.detach();
}

void BaseApp::run()
{
    if (installSegVHandler()) {
        signal(SIGSEGV, &BaseApp::handleSIGSEGV);
    }

    if (installSegIntHandler()) {
        signal(SIGINT, &BaseApp::handleSIGINT);
    }

    handleConfigUpdate();

    appName_ = appCfg_["name"].get<std::string>();

    srand((unsigned)time(0));
    setup(appCfg_);
    startServer();

    if (shouldStartConfigThread()) {
        startConfigThread();
    }
}

void BaseApp::main(int argc, char *argv[], const string &version, BaseApp *app) {
    try {
        app->run();
    } catch (string s) {
        std::cerr << s << std::endl;
    }

    if (app) {
        delete app;
    }
}

void BaseApp::addGrpcService()
{

}
