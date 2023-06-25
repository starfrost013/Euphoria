// Euphoria.cpp : Defines the entry point for the application.
//

#include "Euphoria.h"
#include "tier0/tier0.h"

int main()
{
	printf(u8"%s\n", EUPHORIA_VERSION_FULL);
	printf(u8"Initialising Tier 0\n");
	Tier0_Init();
	return 0;
}
