#pragma once

#define DLLEXPORT extern "C" __declspec(dllexport)

#include <stdio.h>

DLLEXPORT int user(void);