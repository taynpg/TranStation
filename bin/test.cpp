#include <chrono>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "trans_buffer.hpp"
#include <thread>

using namespace transfer;

void test1() {

    char data[128] = {"1"};
    char data1[128] = {"Transfer."};

    char readdata[128] = "";

    data_buffer_v1<char> buffer;
    if (!buffer.allocMem(2)) {
        std::cout << "Alloc failed.." << std::endl;
        return ;
    } 

    buffer.write(data, std::strlen(data));
    buffer.write(data1, std::strlen(data1));

    std::cout << "read len:" << buffer.read(readdata, 64) << std::endl;

}

std::function<void(data_buffer_v2<char>&)> g_call;

void gcall(data_buffer_v2<char>& buffer) {

    char data[128] = "";
    std::memcpy(&data, buffer.getPtr(), buffer.getcur());
    buffer.popData(buffer.getcur());
    std::cout << data << std::endl;
}



data_buffer_v2<char> data;

void test2() {

    char data1[128] = {"Transfer."};

    int i = 0;
    while (++i < 100) {

        std::snprintf(data1, 128, "%s %d", "Tansfer", i);
        data.pushData(data1, std::strlen(data1));
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int main() {

    g_call = gcall;
    data.allocMem(256);
    data.registerCall(g_call);

    std::thread t(test2);


    t.join();

    std::cout << "Buffer当前的游标: " << data.getcur() << std::endl;

    return 0;
}