#ifndef __SERVICE_APP_H__
#define __SERVICE_APP_H__

#include "base/base_app.h"
#include "grpc_server/hello_server.h"


class App : public BaseApp {
  private:
    void setup(const nlohmann::json &) override;
    void start();
    void stop();
    void idle();

  public:
    App();
    ~App() { stop(); };

    App(const App &) = delete;
    App &operator=(const App &) = delete;
    App(App &&) = delete;
    App &operator=(App &&) = delete;

    void run() override;
    void addGrpcService() override;

  private:
    std::unique_ptr<HelloServer> hello_server_impl_;
};

#endif // __SERVICE_APP_H__
