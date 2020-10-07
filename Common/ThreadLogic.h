#ifndef INFOTECSFST_THREADLOGIC_H
#define INFOTECSFST_THREADLOGIC_H

#include <mutex>
#include <condition_variable>
#include "BigNum.h"

class SharedMemory {
public:
    std::mutex lock;
    std::condition_variable holdControl;
    bool isFileEmpty = true;
    const std::string filePath = "test.txt";
};

class IThread {
protected:
    std::shared_ptr<SharedMemory> sharedMemoryPtr;
public:
    IThread(std::shared_ptr<SharedMemory> sharedPtr) : sharedMemoryPtr(sharedPtr) {}

    virtual ~IThread() = default;

    virtual void run() = 0;

    void operator()() { run(); }
};

class Handler : public IThread {
public:
    Handler(std::shared_ptr<SharedMemory> sharedPtr) : IThread(sharedPtr) {}

private:
    bool check(const std::string &expression);

    bool checkNumOnly(const std::string &expression);

    void sortNums(std::string &expression);

    void insertSeparator(std::string &expression);

    void run() override;
};

class Sender : public IThread {
public:
    Sender(std::shared_ptr<SharedMemory> sharedPtr) : IThread(sharedPtr) {}
private:
    void run() override;
};

#endif //INFOTECSFST_THREADLOGIC_H