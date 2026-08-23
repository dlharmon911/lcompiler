#include <stdio.h>
#include "manifest.h"

int main(int argc, char** argv)
{
	manifest_data_t data = { 0 };

	if (manifest_initialize(&data) != 0)
	{
		fprintf(stderr, "Failed to initialize manifest.\n");
		return 1;
	}

	al_rest(5.0);

	manifest_shutdown(&data);

	return 0;
}
