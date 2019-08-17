#include <stdio.h>
#include <string.h>

#ifdef WIN32
    #define SNPRINTF sprintf_s
#else
    #define SNPRINTF snprintf
#endif

void PrintBuffer(void* pBuff, unsigned int nLen)
{
    if (NULL == pBuff || 0 == nLen)
    {
        return;
    }

    int nBytePerLine = 4;
    unsigned char* p = (unsigned char*)pBuff;
    char szHex[3 * 4 + 1] = {0};    // 4 为1行4个16进制。3包含2位的16进制的字符和一个空格
    printf("---------------- begin ------------------\n");
    for (unsigned int i=0; i<nLen; ++i)
    {
        int idx = 3 * (i % nBytePerLine);
        if (0 == idx)
        {
            memset(szHex, 0, sizeof(szHex));
        }
        SNPRINTF(&szHex[idx], 4, "%02x ", p[i]);// buff长度要多传入1个字节

        // 以16个字节为一行，进行打印
        if (0 == ((i+1) % nBytePerLine))
        {
            printf("%s\n", szHex);
        }
    }

    // 打印最后一行未满16个字节的内容
    if (0 != (nLen % nBytePerLine))
    {
        printf("%s\n", szHex);
    }
    printf("----------------- end -------------------\n");
}

int main()
{
	char ch[100] = {0x12, 0x34, 0x98, 0x98, 0x00, 0x00, 0x12, 0x87, 0xaa, 0x22};
	PrintBuffer(ch, 12);
}