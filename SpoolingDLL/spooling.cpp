#include "pch.h"
#include "spooling.h"
#include <stdio.h>

SPOOLING_DEQUE spooling_deque;

void deque_initail(void)
{
	spooling_deque.begin = 0;
	spooling_deque.end = 0;
}

HANDLE mutexPush = CreateMutex(NULL, false, NULL);
HANDLE mutexPop = CreateMutex(NULL, false, NULL);

//int返回值  -1队满
int push_deque(int pid)
{
	printf("push %d\n", pid);//删
	//队列满
	if ((spooling_deque.end + 1) % NODE_MAXSIZE == spooling_deque.begin)
	{
		return -1;
	}
	REQ_BLOCK req;
	req.pid = pid;
	char filePath[20];
	Int_To_Str(pid, filePath);
	strcpy(req.filePath, filePath);

	WaitForSingleObject(mutexPush, INFINITE);

	spooling_deque.node[spooling_deque.end] = req;
	//Sleep(1000);
	spooling_deque.end = (spooling_deque.end + 1) % NODE_MAXSIZE;

	ReleaseMutex(mutexPush);

	return 1;
}

int pop_deque()
{
	int pid = -1;
	if (spooling_deque.end != spooling_deque.begin)
	{
		WaitForSingleObject(mutexPop, INFINITE);
		pid = spooling_deque.node[spooling_deque.begin].pid;
		//Sleep(1000);
		spooling_deque.begin = (spooling_deque.begin + 1) % NODE_MAXSIZE;
		ReleaseMutex(mutexPop);
	}
	return pid;
}

void Int_To_Str(int x, char* Str) {
	int t;
	char* Ptr, Buf[10];
	int i = 0;
	Ptr = Str;
	while (x > 0) {
		t = x % 10;
		x = x / 10;
		Buf[i++] = t + 0x30; // 通过计算把数字编成ASCII码形式  
	}
	i--;
	for (; i >= 0; i--) {
		*(Ptr++) = Buf[i];
	}
	*Ptr = '\0';
}

int devPrint(char* str)
{
	int pid = (int)GetCurrentThreadId();
	printf("提出打印请求：%d\n", pid);
	push_deque(pid);
	//printf("%s\n", str);
	return pid;
}