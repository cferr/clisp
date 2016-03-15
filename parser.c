#include "parser.h"

// when recursively parsing the input string, we still
// seek through this very string, thus we need a pointer
// to pass the position along the recursive calls

/* or we can avoid recursive calls by using a dynamic pointer...
 * Given that environments are double linked trees, we never lose
 * a derivated environment by overwriting a pointer to it! */

// be careful not to forget to externalize the current state
// so that parsing can be resumed (e.g. when pressing RETURN)

void parse(const char* _str, env* _curEnv, bufword** _buf, int _len, 
           unsigned int* _seek)
{
    int automaton_state = STAT_NORMAL;
    env* env = _curEnv;
    unsigned int bufstr_len = 0;
    // switches in a switch ?
    for(; *_seek < _len; (*_seek)++)
    {
        char cc = _str[*_seek];
        switch(automaton_state) 
        {
            case STAT_NORMAL:
                if(cc == ')')
                    env = env->parent;
                else if(cc == '(') {
                    env = derivate(env);
                }
                else if(cc == '"')
                    automaton_state = STAT_STR;
                else {
                    // put chars in the buffer
                    // the ignore rules are to be
                    // defined in the word struct

                    *_buf = bufword_appendc(*_buf, cc);
                }
                break;
            case STAT_STR:
                if(automaton_state & IGNORE || cc != '"') {
                    bufstr_len++;
                    if(!(automaton_state & IGNORE) && cc == '\\')
                        automaton_state |= IGNORE;
                }
                else 
                {
                    // TODO make lea's life easier
                    *_buf = bufword_froms(*_buf, _str + *_seek - bufstr_len,
                        bufstr_len);
                    bufstr_len = 0;
                    automaton_state = STAT_NORMAL;
                }
                break;
        }
    }
    return;
}
