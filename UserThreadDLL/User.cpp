#include "pch.h"
#include "framework.h"
#include "User.h"

typedef int (*FUNTDevPrint)(char *str);
typedef void (*FUNInt_To_Str)(int x, char* Str);

HMODULE SpoolingDLL = LoadLibrary(L"SpoolingDll.dll");

FUNTDevPrint devPrint = (FUNTDevPrint)GetProcAddress(SpoolingDLL, "devPrint");
FUNInt_To_Str Int_To_Str = (FUNInt_To_Str)GetProcAddress(SpoolingDLL, "Int_To_Str");

int user(void)
{
	time_t start, end;
	int pid = (int)GetCurrentThreadId();
	printf("用户线程%d开始:\n", pid);
	char pidStr[30];
	Int_To_Str(pid, pidStr);

	//修正，放入文件夹避免混乱
	char filePath[20] = "outputPool/";
	strcat(filePath, pidStr);

	//char str[] = "1234";
	
	printf("%d写入输出井\n", pid);
	FILE* fp;
	fp = fopen(filePath, "wb");
	fwrite(filePath, sizeof(filePath), 1, fp);
	fclose(fp);
	
	devPrint(filePath);

	return 1;
}
