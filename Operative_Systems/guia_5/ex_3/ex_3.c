#include <stdio.h>
#include <unistd.h>

int main() {
	int fileDes[2], bytesReaded;
	char buffer[256];
	
    if (pipe(fileDes) < 0) {
        perror("pipe function failed");
        _exit(0);
    }

    if (fork()) { // Parent process
		close(fileDes[1]);
		close(0);
		
        dup(fileDes[0]);
		execlp("wc","wc",NULL);
	} else { // Child process
		close(fileDes[0]);
		
        while ((bytesReaded = read(0,buffer,sizeof(buffer))) > 0) 
			write(fileDes[1], buffer, bytesReaded);
		
		wait(NULL);
	}
	return 0;
}