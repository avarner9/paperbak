#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <algorithm>
#include <stdio.h>

#include "fnsplitmerge.h"


static char * strchrnul(const char * s, int c)
{
    const char * retval = strchr(s, c);
    if (retval == NULL)
    {
        retval = s + strlen(s);
    }
    return (char *)retval;
}

int fnsplit(const char * path, char * drive, char * dir, char * name, char * ext)
{
    bool has_drive = false;
    if ((strlen(path) >= 2) && (path[1] == ':'))
    {
        has_drive = true;
        if (drive != NULL)
        {
            strncpy(drive, path, 2);
            drive[2] = '\0';
        }
        path += 2;
    }

    size_t dir_len = 0;
    if (strchr(path, '/') != NULL)
    {
        dir_len = strrchr(path, '/') - path + 1;
    }
    if (strchr(path, '/') != NULL)
    {
        size_t dir_len_2 = strrchr(path, '/') - path + 1;
        if (dir_len_2 > dir_len)
        {
            dir_len = dir_len_2;
        }
    }
    if (dir_len > 0)
    {
        if (dir != NULL)
        {
            size_t copy_size = dir_len;
            if (copy_size > (MAXDIR - 1))
                copy_size = (MAXDIR - 1);
            dir[0] = '\0';
            strncat(dir, path, copy_size);
        }
        path += dir_len;
    }

    size_t name_len = strchrnul(path, '.') - path;
    if (name != NULL)
    {
        size_t copy_size = name_len;
        if (copy_size > (MAXFILE - 1))
            copy_size = (MAXFILE - 1);
        name[0] = '\0';
        strncat(name, path, copy_size);
    }
    path += name_len;

    size_t ext_len = strlen(path);
    if (ext != NULL)
    {
        size_t copy_size = ext_len;
        if (copy_size > (MAXEXT - 1))
            copy_size = (MAXEXT - 1);
        ext[0] = '\0';
        strncat(ext, path, copy_size);
    }

    int retval = 0;
    if (has_drive)
        retval |= DRIVE;
    if (dir_len > 0)
        retval |= DIRECTORY;
    if (name_len > 0)
        retval |= FILENAME;
    if (ext_len > 0)
        retval |= EXTENSION;

    return retval;
}
void fnmerge(char * path, const char * drive, const char * dir, const char * name, const char * ext)
{
    if (drive == NULL)
        drive = "";
    if (dir == NULL)
        dir = "";
    if (name == NULL)
        name = "";
    if (ext == NULL)
        ext = "";
    snprintf(path, MAXPATH, "%s%s%s%s", drive, dir, name, ext);
}

