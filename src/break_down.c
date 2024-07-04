#include "break_down.h"
int break_down(char *text, char *temp, int *pos, int size,int *t_size)
{
    if ((*pos)+1 > size)
        return 0;
    enum
    {
        STATE_START = 0,
        STATE_CR,
        STATE_CRLF,
        STATE_CRLFCR,
        STATE_CRLFCRLF
    };
    int state;
    *t_size=0;
    size_t offset = 0;
    char ch;
    memset(temp, 0, 4096);
    state = STATE_START;
    while (state != STATE_CRLFCRLF)
    {
        char expected = 0;
        if (*pos == size)
            break;
        ch = text[(*pos)++];
        (*t_size)++;
        temp[offset++] = ch;
        //printf("ch:%c\n",ch);
        switch (state)
        {
        case STATE_START:
        case STATE_CRLF:
            expected = '\r';
            break;
        case STATE_CR:
        case STATE_CRLFCR:
            expected = '\n';
            break;
        default:
            state = STATE_START;
            continue;
        }
        if (ch == expected)
            state++;
        else
            state = STATE_START;
        //printf("state:%d\n",state);
    }
    //printf("pos:%d\n",*pos);
    //printf("size:%d\n",size);
    return 1;
}