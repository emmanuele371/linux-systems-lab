#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> // for O_RDONLY

int main() {
	int file_descriptor = open("/dev/urandom", O_RDONLY); // open in read-only mode
	int random_data;
	size_t read_data = read(file_descriptor, &random_data, 4);
	printf("%08x\n", random_data);
	return 0;
}
