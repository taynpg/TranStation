#include <cstring>
#include <iostream>
#include "trans_buffer.hpp"

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
    std::cout << "Done" << std::endl;
}

void test2() {

    g_call = gcall;
    char data1[128] = {"Transfer."};
    data_buffer_v2<char> data;

    data.allocMem(256);
    data.registerCall(g_call);

    data.pushData(data1, std::strlen(data1));

}

int main() {

    test2();

    return 0;
}