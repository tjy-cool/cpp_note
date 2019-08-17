#include <stdio.h>
#include <stdlib.h>

int read_file(const char* file_name, int* file_size, char** ppDataBuf);
int write_file(const char* file_name, const char* pDataBuf, unsigned long file_size);

int main(int argc, char* argv[])
{
	
	if(argc != 3)
	{
		printf("error input, must be two param\n");
		return -1;
	}
	
	int file_size = 0;
	char* pDataBuf = NULL;
	read_file(argv[1], &file_size, &pDataBuf);
	printf("file_size: %d\n", file_size);
	printf("pDataBuf: %p\n", pDataBuf);
	
	write_file(argv[2], pDataBuf, file_size);
	return 0;
}

int read_file(const char* file_name, int* pFileSize, char** ppDataBuf)
{
	FILE* fp = NULL;
	int file_size = 0;
	char* f_data = NULL;
	
	fp = fopen(file_name, "rb");
	if(fp == NULL)
	{
		printf("%d, open file faild\n", __LINE__);
		return -2;
	}
	
	fseek(fp, 0, SEEK_END);
	
	file_size = ftell(fp);
	if (file_size < 0)
    {
        printf("%d, get file size faild\n", __LINE__);
        return -3;
    }
	
	f_data = (char*)malloc(file_size + 1);
	rewind(fp);
	int ret = fread(f_data, sizeof(char), file_size, fp);
	if(ret != file_size)
	{
		printf("%d, read file faild\n", __LINE__);
		return -4;
	}
	
	*pFileSize = file_size;
	*ppDataBuf = f_data;
	
	fclose(fp);
	return 0;
}

int write_file(const char* file_name, const char* pDataBuf, unsigned long file_size)
{
	FILE* fp = NULL;

	fp = fopen(file_name, "w");
	if(fp == NULL)
	{
		printf("%d, open file faild\n", __LINE__);
		return -2;
	}
	
	fwrite(pDataBuf, sizeof(char), file_size, fp);
	fclose(fp);
	return 0;
}
