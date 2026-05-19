#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>

// Simple process info demo with an alarm trigger.

int main() {
	int process_id = getpid();
	char* login_name = (getlogin() != NULL) ? getlogin() : "Unkown User";
	char* dir_name = (get_current_dir_name() != NULL) ? get_current_dir_name() : "Unkown Folder";	
	
	printf("Programm ID: %i\nUser: %s\nWorking Directory: %s", process_id, login_name, dir_name);

	alarm(2);
	sleep(10);
	
	printf("Alarm clock");
	return 0;
}
