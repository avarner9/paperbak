#include <dir.h>

#define MAXPATH (256)
#define MAXDRIVE (3)
#define MAXDIR (256)
#define MAXFILE (256)
#define MAXEXT (20)

#define EXTENSION   (1)
#define FILENAME    (2)
#define DIRECTORY   (4)
#define DRIVE       (8)
#define WILDCARDS   (16)

int fnsplit(const char * path, char * drive, char * dir, char * name, char * ext);
void fnmerge(char * path, const char * drive, const char * dir, const char * name, const char * ext);

