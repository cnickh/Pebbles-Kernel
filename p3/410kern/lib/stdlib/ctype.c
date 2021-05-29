/*
 * ctype.c
 * Modified for 15-410 at CMU
 * Zachary Anderson(zra)
 */

#include <ctype.h>

inline int isascii(int c)
{
        return ((c & ~0x7f) == 0);
}

inline int iscntrl(int c)
{
        return ((c) < ' ') || ((c) > 126);
}

inline int isdigit(int c)
{
        return ((c) >= '0') && ((c) <= '9');
}

inline int isgraph(int c)
{
        return ((c) > ' ') && ((c) <= 126);
}

inline int islower(int c)
{
        return (c >= 'a') && (c <= 'z');
}

inline int isprint(int c)
{
        return ((c) >= ' ') && ((c) <= 126);
}

inline int isspace(int c)
{
        return ((c) == ' ') || ((c) == '\f')
                || ((c) == '\n') || ((c) == '\r')
                || ((c) == '\t') || ((c) == '\v');
}

inline int isupper(int c)
{
        return (c >= 'A') && (c <= 'Z');
}

inline int isxdigit(int c)
{
        return isdigit(c) ||
                ((c >= 'A') && (c <= 'F')) ||
                ((c >= 'a') && (c <= 'f'));
}

inline int isalpha(int c)
{
        return islower(c) || isupper(c);
}

inline int isalnum(int c)
{
        return isalpha(c) || isdigit(c);
}

inline int ispunct(int c)
{
        return isgraph(c) && !isalnum(c);
}

inline int toascii(int c)
{
        return ((c) & 0x7f);
}

inline int toupper(int c)
{
        return ((c >= 'a') && (c <= 'z')) ? (c - 'a' + 'A') : c;
}

inline int tolower(int c)
{
        return ((c >= 'A') && (c <= 'Z')) ? (c - 'A' + 'a') : c;
}
