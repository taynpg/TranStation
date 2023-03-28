#include <iostream>
#include "trans_buffer.hpp"

using namespace transfer;

int main() {

    char data[128] = {"1"};
    char data1[128] = {"Transfer."};

    char readdata[128] = "";

    data_buffer_v1<char> buffer;
    if (!buffer.allocMem(2)) {
        std::cout << "Alloc failed.." << std::endl;
        return -1;
    } 

    buffer.write(data, std::strlen(data));
    buffer.write(data1, std::strlen(data1));

    std::cout << "read len:" << buffer.read(readdata, 64) << std::endl;

    return 0;
}