#pragma once

#include "Core.h"
#include <Windows.h>

class Launcher
{
public:
	Launcher();
	~Launcher();

	void Update();
private:
	PROCESS_INFORMATION pi;
	bool engineActive = false;
};

