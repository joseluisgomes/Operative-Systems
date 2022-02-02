#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char const *argv[]) {
    mkfifo("C:\\Users\\User\\OneDrive\\Documents\\GitHub\\Operative-Systems\\Operative_Systems\\guia_6\\ex_1", 0666);

    return 0;
}
