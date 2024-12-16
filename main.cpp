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

struct header_format
{
uint16_t header_crc;
uint8_t header_type;
uint16_t header_flags;
uint16_t header_size;
};


#pragma pack(pop)


int main()
{
    ifstream rar_file("Example.rar", ios::binary);
    if (!rar_file.is_open())
    {
        cout << "Not open file" << endl;
            return 1;
    }

    rar_file.seekg(0, ios::end);
    int fileSize = rar_file.tellg();
    cout << "File size: " << fileSize << " bytes" << endl;
    rar_file.seekg(0, ios::beg);
    vector<char> rar_data(fileSize, 0);
    rar_file.read(rar_data.data(), fileSize);



return 0;
}
