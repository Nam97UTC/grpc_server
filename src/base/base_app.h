#ifndef SERVICE_BASE_APP_H
#define SERVICE_BASE_APP_H


#include <grpcpp/server_builder.h>
#include <string>
#include <vector>
#include "modern_json.hpp"

class BaseApp {
  private:
    nlohmann::json appCfg_;

    void readConfiguration(nlohmann::json &appCfg);
    void configThread();
    void startConfigThread();

    static void handleSIGSEGV(int sig);
    static void handleSIGINT(int sig);

    void handleConfigUpdate();
    void startServer();

  protected:
    std::string appName_;
    grpc::ServerBuilder grpcBuilder_;
    std::unique_ptr<grpc::Server> rpcServer_;

    virtual void setup(const nlohmann::json &appCfg_) = 0;
    virtual bool shouldStartConfigThread() { return true; }
    virtual bool installSegVHandler() { return true; }
    virtual bool installSegIntHandler() { return false; }
    virtual void addGrpcService();

    nlohmann::json appCfg() { return appCfg_; }

  public:
    BaseApp() {}
    virtual ~BaseApp() {}
    virtual void run();

    BaseApp(const BaseApp &) = delete;
    BaseApp &operator=(const BaseApp &) = delete;
    BaseApp(BaseApp &&) = delete;
    BaseApp &operator=(BaseApp &&) = delete;

    static void main(int argc, char *argv[], const std::string &version, BaseApp *app);
};

#endif // SERVICE_BASE_APP_H
