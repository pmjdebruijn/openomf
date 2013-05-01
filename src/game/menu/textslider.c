#include "game/menu/textslider.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

void textslider_create(component *c, font *font, const char *text, unsigned int positions) {
    component_create(c);
    textslider *tb;
    tb = malloc(sizeof(textslider));
    tb->text = text;
    tb->font = font;
    tb->ticks = 0;
    tb->dir = 0;
    tb->pos = 1;
    tb->positions = positions;
    c->obj = tb;
    c->render = textslider_render;
    c->event = textslider_event;
    c->tick = textslider_tick;
}

void textslider_free(component *c) {
    textslider *tb = c->obj;
    free(tb);
    component_free(c);
}

void textslider_render(component *c) {
    textslider *tb = c->obj;
    char buf[100];
    int chars;
    int width;
    int xoff;
    sprintf(buf, "%s ", tb->text);
    chars = strlen(buf);
    for(int i = 0; i < tb->positions; i++) {
        if (i+1 > tb->pos) {
            buf[chars+i] = '|';
        } else {
            buf[chars+i] = 127;
        }
    }
    // null terminator
    buf[chars+tb->positions] = '\0';
    chars = strlen(buf);
    width = chars*tb->font->w;
    xoff = (c->w - width)/2;
    if(c->selected) {
        int t = tb->ticks / 2;
        font_render(tb->font, buf, c->x + xoff, c->y, 80 - t, 220 - t*2, 80 - t);
    } else if (c->disabled) {
        font_render(tb->font, buf, c->x + xoff, c->y, 121, 121, 121);
    } else {
        font_render(tb->font, buf, c->x + xoff, c->y, 0, 121, 0);
    }
}

int textslider_event(component *c, SDL_Event *event) {
    // Handle selection
    textslider *tb = c->obj;
    switch(event->type) {
        case SDL_KEYDOWN:
            if(event->key.keysym.sym == SDLK_RETURN || event->key.keysym.sym == SDLK_RIGHT) {
                tb->pos++;
                if (tb->pos >= tb->positions) {
                    tb->pos = tb->positions;
                }
                return 0;
            } else  if(event->key.keysym.sym == SDLK_LEFT) {
                tb->pos--;
                if (tb->pos < 1) {
                    tb->pos = 1;
                }
                return 0;
            }
    }
    return 1;
}

void textslider_tick(component *c) {
    textslider *tb = c->obj;
    if(!tb->dir) {
        tb->ticks++;
    } else {
        tb->ticks--;
    }
    if(tb->ticks > 120) {
        tb->dir = 1;
    }
    if(tb->ticks == 0) {
        tb->dir = 0;
    }
}