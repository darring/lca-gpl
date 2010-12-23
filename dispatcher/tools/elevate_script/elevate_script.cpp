#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// This elevates scripts to a given UID
// usage:
// elevate_script UID /foo/bar/script.sh
int main(int argc, char *argv[])
{
    if(argc != 2) {
        // We must be run with two arguments!
        return -1;
    }

    int UID = atoi(argv[0]);
    char *script = argv[1];

    setuid( UID );
    system( script );

    return 0;
}
