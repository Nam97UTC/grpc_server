
#include "app.h"
#include "base/base_app.h"

using namespace std;

const std::string VERSION{"123456"};

int main(int argc, char *argv[])
{
    BaseApp::main(argc, argv, VERSION, new App());
    return 0;
}
