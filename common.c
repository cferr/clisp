#include "common.h"

bufword* new_bufword()
{
    bufword* new = (bufword*)malloc(sizeof(bufword));
    new->next = NULL;
    new->len = 0;
    new->wd = (char*)calloc(BASE_ALLOCATION_LENGTH, sizeof(char));
    new->allocd_len = BASE_ALLOCATION_LENGTH;

    return new;
}

// there's no reason to have c const...
bufword* bufword_appendc(bufword* _buf, char c)
{
    if(c != ' ')
    {
        // the +1 is here to remind us of the zero terminator
        if(_buf->allocd_len == _buf->len + 1)
        {
            _buf->wd = (char*)realloc(_buf->wd, _buf->allocd_len + 
                BASE_ALLOCATION_LENGTH);
            _buf->allocd_len += BASE_ALLOCATION_LENGTH;
        }

        _buf->wd[_buf->len] = c;
        _buf->wd[_buf->len + 1] = 0x00;
        _buf->len += 1;
        return _buf;
    }
    else
    {
        bufword* new = new_bufword();
        _buf->next = new;
        return new;
    }
    return NULL; // should NEVER HAPPEN
}

bufword* bufword_froms(bufword* _buf, const char* _s, int _len)
{
    // when this function is called, we're necessarily after a 
    // whitespace
    // thus we've got an empty bufword
    assert(_buf->len == 0);
    while(_buf->allocd_len < _len + 1)
    {
        _buf->wd = (char*)realloc(_buf->wd, _buf->allocd_len +
            BASE_ALLOCATION_LENGTH);
        _buf->allocd_len += BASE_ALLOCATION_LENGTH;
    }
    strncpy(_buf->wd, _s, _len);
    return _buf;
}

