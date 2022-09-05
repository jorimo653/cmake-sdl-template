#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_ttf.h>

#define WINDOW_WIDTH        640
#define WINDOW_HEIGHT       480


void print_error(char *error_type) {
    printf("%s Error: %s\n", error_type, SDL_GetError());
}

SDL_Texture* load_texture(const char* file, SDL_Renderer *renderer) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, file);
    if (texture == NULL) {
        print_error("load_texture");
    }
    return texture;
}

void render_texture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

int main(int argc, char **argv) {
    printf("Hello, World!\n");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        print_error("SDL_Init");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL_Template", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_DestroyWindow(window);
        print_error("SDL_CreateWindow");
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        print_error("SDL_CreateRenderer");
        return 1;
    }

    const char* path = strcat(SDL_GetBasePath(), "res/img/galaxybrain.png");
    SDL_Texture *image = load_texture(path, renderer);
    if (image == NULL) {
        print_error("SDL_CreateTexture");
        SDL_DestroyTexture(image);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    render_texture(image, renderer, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    SDL_RenderPresent(renderer);

//    TTF_Font *font = TTF_OpenFont("res/fonts/BoogieNightsShadowNF.ttf", 24);
//    const SDL_Color white = {255,255,255};
//    SDL_Surface *surface_msg = TTF_RenderText_Solid(font, "It's Showtime", white);
//    SDL_Texture *msg_texture = SDL_CreateTextureFromSurface(renderer, surface_msg);

//    SDL_Rect *msg_rect = malloc(sizeof(SDL_Rect));
//    msg_rect->x = WINDOW_WIDTH / 2;
//    msg_rect->y = WINDOW_HEIGHT / 2;
//    msg_rect->w = 300;
//    msg_rect->h = 400;

//    SDL_RenderCopy(renderer, msg_texture, NULL, &msg_rect);
//
    SDL_Delay(6000);
//
//    //cleanup
//    SDL_FreeSurface(surface_msg);
//    SDL_DestroyTexture(msg_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    printf("Base path: %s\n", SDL_GetBasePath());

    SDL_Quit();

    return 0;
}
