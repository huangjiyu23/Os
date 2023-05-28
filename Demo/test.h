#pragma once

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE 512

char inputBuffer[BUFFERSIZE];//输入缓冲区
char outputBuffer[BUFFERSIZE + 1];//输出缓冲区

void outputProcess();
void loadDLL();
