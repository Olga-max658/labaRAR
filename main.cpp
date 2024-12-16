#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <windows.h>

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

void readRar(vector<char>& rar_data)
{
    header_format* p_header = reinterpret_cast<header_format*>(&rar_data[7]);
    int offset = 7 + int(p_header -> header_size);
    while (true)
    {
        header_format* p_header = reinterpret_cast <header_format*> (&rar_data[offset]);
        file_header* f_header = reinterpret_cast <file_header*> (&rar_data[offset+7]);
        if (p_header -> header_type == 0x74)
        {
            uint16_t sizeHeader = f_header -> NameSize;
            uint16_t offsetHeader = offset + sizeof (struct header_format) + sizeof (struct file_header);
            if (offsetHeader + sizeHeader > rar_data.size())
            {
                break;
            }
            char* jumpCell = reinterpret_cast<char*>(&rar_data[offsetHeader]);
            string utf8line(jumpCell, sizeHeader);
            vector <wchar_t> utf16content(sizeHeader);
            MultiByteToWideChar(CP_UTF8,0,utf8line.c_str(),sizeHeader,utf16content.data(),utf16content.size());
            wstring FileName(utf16content.begin(),utf16content.end());
            wcout << "Name file: " << FileName << endl;
            offset = offset + p_header -> header_size + f_header -> PackSize;
        }
        else
        {
            offset += p_header->header_size;
        }

    }

};


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
    readRar(rar_data);

return 0;
}
