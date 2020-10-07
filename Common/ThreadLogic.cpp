#include "ThreadLogic.h"
#include "BigNum.h"
#include <algorithm>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

bool Handler::check(const std::string &expression) {
    return (expression.length() <= 64) && (checkNumOnly(expression));
}

bool Handler::checkNumOnly(const std::string &expression) {
    for (char i : expression) {
        if (i < '0' || i > '9') {
            return false;
        }
    }
    return true;
}

void Handler::sortNums(std::string &expression) {
    std::sort(expression.begin(), expression.end(), [](char a, char b) { return a > b; });
}

void Handler::insertSeparator(std::string &expression) {
    std::string rez;
    for (char i : expression) {
        if ((i - '0') % 2 == 0) {
            rez += "KB";
        } else {
            rez += i;
        }
    }
    expression = rez;
}

void Handler::run() {
    while (true) {
        {
            std::string curLine;
            std::cin >> curLine;
            if (check(curLine)) {
                sortNums(curLine);
                insertSeparator(curLine);
                {
                    std::unique_lock<std::mutex> ul(sharedMemoryPtr->lock);
                    std::ofstream wr(sharedMemoryPtr->filePath, std::ios_base::out | std::ios_base::app);
                    wr << curLine << std::endl;
                    wr.close();
                    sharedMemoryPtr->isFileEmpty = false;
                    sharedMemoryPtr->holdControl.notify_one();
                }
            }
        }
    }
}

void Sender::run() {
    while (true) {
        std::vector<std::string> input;
        {
            std::unique_lock<std::mutex> ul(sharedMemoryPtr->lock);
            sharedMemoryPtr->holdControl.wait(ul, [this]() { return !sharedMemoryPtr->isFileEmpty; });
            std::ifstream rd(sharedMemoryPtr->filePath, std::ios_base::in);
            std::string nums;
            while (!rd.eof()) {
                getline(rd, nums);
                if (nums != "") {
                    input.push_back(nums);
                }
            }

            rd.close();
            std::ofstream wr(sharedMemoryPtr->filePath, std::ios_base::trunc);
            wr.close();
            sharedMemoryPtr->isFileEmpty = true;
        }
        for (std::string str : input) {
            BigNum ans;
            ans.parse(str);
            std::string rez = ans.toString();
            std::cout << "Received line: " << str << ". Result after computing: " << rez << std::endl;

            int sock = socket(AF_INET, SOCK_STREAM, 0);
            sockaddr_in newAddr;
            newAddr.sin_family = AF_INET;
            newAddr.sin_port = htons(1234);
            newAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

            int res = connect(sock, (struct sockaddr *) &newAddr, sizeof(newAddr));
            if (res == -1) {
                std::cout << "Connection failed!" << std::endl;
            } else {
                char *curBuf = const_cast<char *>(rez.c_str());
                int bufLen = rez.length();
                send(sock, &bufLen, 1, MSG_NOSIGNAL);
                send(sock, curBuf, bufLen, MSG_NOSIGNAL);
            }
            shutdown(sock, SHUT_WR);
            close(sock);
        }
    }
}