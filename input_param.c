#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
int
main(int argc, const char **argv)
{
  assert(argc == 3);
	const char *path = argv[1];
	const char *filename = argv[2];
	char command[200];

	snprintf(command, sizeof(command), "%s < %s", path, filename);
  system(command);
}
