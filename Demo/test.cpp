#include "test.h"

//load dll
typedef int (*FUNuser)(void);
typedef int (*FUNdevPrint)(char* str);
typedef void (*FUNInitial)(void);
typedef int (*FUNPop)(void);
typedef void (*FUNInt_To_Str)(int x, char* Str);

FUNuser user;
FUNdevPrint devPrint;
FUNInitial deque_initail;
FUNPop deque_pop;
FUNInt_To_Str Int_To_Str;

void main(void)
{
	loadDLL();

	CreateThread(NULL, 512, (LPTHREAD_START_ROUTINE)outputProcess, NULL, 0, NULL);

	char tempName[20];
	char fileName[10][20];
	int count = 0;
	count = 1;

	for (int i = 0; i < count; i++)
	{
		CreateThread(NULL, 512, (LPTHREAD_START_ROUTINE)user, NULL, 0, NULL);
	}
	while (1) {
		;
	}
}

void inputProcess()
{

}

void outputProcess()
{
	printf("输出进程开始执行\n");
	
	int pid = -1;
	char pidStr[20];

	while (1)
	{
		pid = deque_pop();
		if (pid == -1)
		{
			continue;
		}
		printf("pop %d\n", pid);//删
		Int_To_Str((int)pid, pidStr);
		printf("进程 %s 开始打印.\n", pidStr);
		FILE* fp;

		//修正，放入文件夹避免混乱
		char filePath[20] = "outputPool/";
		strcat(filePath, pidStr);

		fp = fopen(filePath, "r");
		if (fp == NULL)
		{
			printf("failed to open file.\n");
			continue;
		}
		while (fread(outputBuffer, sizeof(char), BUFFERSIZE, fp) != 0)
		{
			outputBuffer[BUFFERSIZE] = '\0';
			printf("打印内容: %s\n", outputBuffer);
		}
		fclose(fp);
	}
}

void loadDLL()
{
	HMODULE SpoolingDll = LoadLibrary(L"SpoolingDll.dll");
	if (SpoolingDll == NULL) {
		MessageBox(NULL, L"Error loading spooler.dll", NULL, NULL);
	}
	devPrint = (FUNdevPrint)GetProcAddress(SpoolingDll, "devPrint");
	deque_initail = (FUNInitial)GetProcAddress(SpoolingDll, "deque_initail");
	deque_pop = (FUNPop)GetProcAddress(SpoolingDll, "pop_deque");
	Int_To_Str = (FUNInt_To_Str)GetProcAddress(SpoolingDll, "Int_To_Str");

	HMODULE UserDLL = LoadLibrary(L"UserThreadDLL.dll");
	if (UserDLL == NULL)
	{
		printf("failed to load UserDLL.\n");
	}
	user = (FUNuser)GetProcAddress(UserDLL, "user");
}