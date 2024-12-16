#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>

using namespace std;

#pragma pack(push, 1)

struct file_header
{
uint32_t PackSize;
uint32_t UnpSize;
uint8_t HostOS;
uint32_t FileCRC;
uint32_t FileTime;
uint8_t UnpVer;
uint8_t Method;
uint16_t NameSize;
uint32_t FileAttr;
};


#pragma pack(pop)


int main()
{


return 0;
}
