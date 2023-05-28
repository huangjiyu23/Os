#pragma once

#define DLLEXPORT extern "C" __declspec(dllexport)

#define NODE_MAXSIZE 100

struct REQ_BLOCK
{
	int pid = -1;
	char filePath[20];
};

struct SPOOLING_DEQUE
{
	REQ_BLOCK node[NODE_MAXSIZE];
	int begin;
	int end;
};


extern SPOOLING_DEQUE spooling_deque;

DLLEXPORT void deque_initail(void);
DLLEXPORT int push_deque(int pid);
DLLEXPORT int pop_deque();
DLLEXPORT void Int_To_Str(int x, char* Str);
DLLEXPORT int devPrint(char* str);