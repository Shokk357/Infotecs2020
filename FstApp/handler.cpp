#include "../Common/ThreadLogic.h"
#include <thread>

int main() {
    std::shared_ptr<SharedMemory> mem = std::make_shared<SharedMemory>();
    Handler handler(mem);
    Sender sender(mem);
    std::thread handlerTh(handler);
    std::thread senderTh(sender);
    handlerTh.join();
    senderTh.join();
    return 0;
}