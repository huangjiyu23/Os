#pragma once

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE 512

char inputBuffer[BUFFERSIZE];//���뻺����
char outputBuffer[BUFFERSIZE + 1];//���������

void outputProcess();
void loadDLL();
