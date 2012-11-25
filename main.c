#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include <stdint.h>
typedef int64_t  s64;
typedef int32_t  s32;
typedef int16_t  s16;
typedef int8_t    s8;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t   u8;

#include "_ceu_defs.h"

#ifndef IN_SDL_DT
s32 WCLOCK_nxt;
#define ceu_out_wclock(us) WCLOCK_nxt = us;
#endif

#ifdef CEU_ASYNCS
int ASYNC_nxt = 0;
#define ceu_out_async(v) ASYNC_nxt = v;
#endif

#include "_ceu_code.cceu"

int main (int argc, char *argv[])
{
    int ret;

    SDL_Init(SDL_INIT_EVERYTHING);

#ifdef IN_SDL_DT
    WCLOCK_nxt = 20000;
#else
    WCLOCK_nxt = CEU_WCLOCK_NONE;
#endif

#if defined(CEU_WCLOCKS) || defined(CEU_ASYNCS)
    u32 old = SDL_GetTicks();
#endif

    if (ceu_go_init(&ret))
        goto END;

#ifdef IN_START
    if (ceu_go_event(&ret, IN_START, NULL))
        goto END;
#endif

    SDL_Event evt;
    for (;;)
    {
#ifndef SDL_SIMUL

        s32 tm = 0;
#ifdef CEU_WCLOCKS
        tm = WCLOCK_nxt / 1000;
#endif
#ifdef CEU_ASYNCS
        if (ASYNC_nxt)
            tm = 0;
#endif

        int has = SDL_WaitEventTimeout(&evt, tm);

#if defined(CEU_WCLOCKS) || defined(CEU_ASYNCS)
        u32 now = SDL_GetTicks();
#endif

        // OTHER EVENTS
        if (has)
        {
            switch (evt.type) {
    #ifdef IN_SDL_QUIT
                case SDL_QUIT:
                    if (ceu_go_event(&ret, IN_SDL_QUIT, NULL))
                        goto END;
                    break;
    #endif
    #ifdef IN_SDL_KEYDOWN
                case SDL_KEYDOWN: {
                    if (ceu_go_event(&ret, IN_SDL_KEYDOWN, &evt))
                        goto END;
                    break;
                }
    #endif
    #ifdef IN_SDL_KEYUP
                case SDL_KEYUP: {
                    if (ceu_go_event(&ret, IN_SDL_KEYUP, &evt))
                        goto END;
                    break;
                }
    #endif
    #ifdef IN_SDL_MOUSEMOTION
                case SDL_MOUSEMOTION: {
                    if (ceu_go_event(&ret, IN_SDL_MOUSEMOTION, &evt))
                        goto END;
                    break;
                }
    #endif
    #ifdef IN_SDL_MOUSEBUTTONDOWN
                case SDL_MOUSEBUTTONDOWN: {
                    if (ceu_go_event(&ret, IN_SDL_MOUSEBUTTONDOWN, &evt))
                        goto END;
                    break;
                }
    #endif
    #ifdef IN_SDL_MOUSEBUTTONUP
                case SDL_MOUSEBUTTONUP: {
                    if (ceu_go_event(&ret, IN_SDL_MOUSEBUTTONUP, &evt))
                        goto END;
                    break;
                }
    #endif
            }
        }

#if defined(CEU_WCLOCKS) || defined(CEU_ASYNCS)
        s32 dt = now - old;
        old = now;
#endif

#ifdef CEU_WCLOCKS
        if (WCLOCK_nxt != CEU_WCLOCK_NONE) {
            s32 nxt;
            int s = ceu_go_wclock(&ret, 1000*dt, &nxt);
            while (nxt <= 0)
                s = ceu_go_wclock(&ret, 0, &nxt);
            if (s)
                goto END;
        }
#endif

#ifdef IN_SDL_DT
        if (ceu_go_event(&ret, IN_SDL_DT, &dt))
            goto END;
#endif

#ifdef IN_SDL_REDRAW
        if (ceu_go_event(&ret, IN_SDL_REDRAW, NULL))
            goto END;
#endif

#endif  // CEU_SIMUL

#ifdef CEU_ASYNCS
        if (ASYNC_nxt) {
            if (ceu_go_async(&ret, NULL))
                goto END;
        }
#endif
    }
END:
    //SDL_Quit();         // TODO: slow
    return ret;
}

