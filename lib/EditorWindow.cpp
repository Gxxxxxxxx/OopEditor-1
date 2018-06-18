#include "EditorWindow.h"

#include <iostream>

/*
 * Log an SDL error with some error message to the output stream of our choice
 * @param os The output stream to write the message too
 * @param msg The error message to write, format will be msg error: SDL_GetError()
 */
void EditorWindow::logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}

/*
 * Draw an SDL_Texture to an SDL_Renderer at some destination rect
 * taking a clip of the texture if desired
 * @param tex The source texture we want to draw
 * @param rend The renderer we want to draw too
 * @param dst The destination rectangle to render the texture too
 * @param clip The sub-section of the texture to draw (clipping rect)
 *		default of nullptr draws the entire texture
 */
void EditorWindow::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip) {
    SDL_RenderCopy(ren, tex, clip, &dst);
}

/*
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
 * the texture's width and height and taking a clip of the texture if desired
 * If a clip is passed, the clip's width and height will be used instead of the texture's
 * @param tex The source texture we want to draw
 * @param rend The renderer we want to draw too
 * @param x The x coordinate to draw too
 * @param y The y coordinate to draw too
 * @param clip The sub-section of the texture to draw (clipping rect)
 *		default of nullptr draws the entire texture
 */
void EditorWindow::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != nullptr){
        dst.w = clip->w;
        dst.h = clip->h;
    }
    else {
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    }
    renderTexture(tex, ren, dst, clip);
}

/*
 * Render the message we want to display to a texture for drawing
 * @param message The message we want to display
 * @param fontFile The font we want to use to render the text
 * @param color The color we want the text to be
 * @param fontSize The size we want the font to be
 * @param renderer The renderer to load the texture in
 * @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
 */
SDL_Texture* EditorWindow::renderText(const std::string &message, const std::string &fontFile, SDL_Color color,
                                      int fontSize, SDL_Renderer *renderer) {
    //Open the font
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr){
        logSDLError(std::cout, "TTF_OpenFont");
        return nullptr;
    }


//    int w,h;
//    if(TTF_SizeText(font,"IIII",&w,&h)) {
//        // perhaps print the current TTF_GetError(), the string can't be rendered...
//        std::cout << "ERROR" << std::endl;
//    } else {
//        printf("width=%d height=%d\n",w,h);
//    }

    //We need to first render to a surface as that's what TTF_RenderText returns, then
    //load that surface into a texture
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
    if (surf == nullptr){
        TTF_CloseFont(font);
        logSDLError(std::cout, "TTF_RenderText");
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (texture == nullptr){
        logSDLError(std::cout, "CreateTexture");
    }
    //Clean up the surface and font
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return texture;
}

/*
 * Used for cursor flash implement.
 */
Uint32 my_callbackfunc(Uint32 interval, void *param) {

    SDL_Event event;
    SDL_UserEvent userevent;

    /* In this example, our callback pushes an SDL_USEREVENT event
    into the queue, and causes our callback to be called again at the
    same interval: */

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}

/*
 * Construction function
 */
EditorWindow::EditorWindow():window(nullptr),renderer(nullptr){

    //Start up SDL and make sure it went ok
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0){
        logSDLError(std::cout, "SDL_Init");
        throw std::runtime_error("Can not initialize SDL!!");
    }

    //Also need to init SDL_ttf
    if (TTF_Init() != 0){
        logSDLError(std::cout, "TTF_Init");
        SDL_Quit();
        throw std::runtime_error("Can not initialize TTF!!");
    }

    //Setup our window and renderere
    window = SDL_CreateWindow("OopEditor", SDL_WINDOWPOS_CENTERED,
                     SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr){
        logSDLError(std::cout, "CreateWindow");
        TTF_Quit();
        SDL_Quit();
        throw std::runtime_error("Can not create window.");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        logSDLError(std::cout, "CreateRenderer");
        cleanup(window);
        TTF_Quit();
        SDL_Quit();
        throw std::runtime_error("Can not create renderer.");
    }

    timerID = SDL_AddTimer( 500, my_callbackfunc, nullptr);
}


/*
 * Decomposition function
 */
EditorWindow::~EditorWindow() {
}

/*
 * Display the window
 */
void EditorWindow::show(){

    SDL_StartTextInput();

    int l;
    std::string text,tstr;
    SDL_Texture *image;

    while (!quit){
        //Event Polling
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
                quit = true;
            }
            if (e.type == SDL_TEXTINPUT || (e.type == SDL_KEYDOWN && e.key.repeat == 0)){
                if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0){
                    l = text.length();
                    text = text.substr(0,l-1);
                    cursor.moveBackward();
                    std::cout << "Delete word!" << std::endl;
                }
                else if(e.type == SDL_TEXTINPUT){
                    tstr = e.text.text;
                    text += tstr;
                    cursor.moveForward();
                    std::cout << "e.text.text.length " << tstr.length() << ' ' << e.text.text << std::endl;
                }
                std::cout << "text length = "<<text.length() << " Text is -> " << text << std::endl;
            }
            if(e.type == SDL_USEREVENT){
                std::cout << "change visibility." << std::endl;
                cursor.changeVisibility();
            }
        }
        SDL_RenderClear(renderer);

        //draw a rectangle
        SDL_Rect r;
        r.x = 0;
        r.y = 600;
        r.w = 10;
        r.h = 10;

        //SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
        //SDL_RenderDrawRect(renderer,&r);


        //We can draw our message as we do any other texture, since it's been
        //rendered to a texture
        if(text.size() > 0){
            for(int i = 0;text.length() > CHARACTERS_PER_ROW*i ;++i ){
                image = renderText(text.substr(i*CHARACTERS_PER_ROW,CHARACTERS_PER_ROW), TTF_file, color, 64, renderer);
                renderTexture(image, renderer, 0, i*80);
            }
        }

//        SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 20, 20 };
//        SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
//        SDL_RenderFillRect( renderer, &fillRect );

        //Draw cursor
        if(cursor.isVisable()){
            SDL_Rect cursorRect = { cursor.get_x(), cursor.get_y(), cursor.get_cursorWidth(),cursor.get_cursorHeight()};
            SDL_SetRenderDrawColor(renderer,cursorColor.r,cursorColor.g,cursorColor.b,cursorColor.a);
            SDL_RenderFillRect( renderer, &cursorRect);
        }

        //if we don't SDL_SetRenderDrawColor again
        SDL_SetRenderDrawColor( renderer,backColor.r,backColor.g,backColor.b,backColor.a);
        SDL_RenderPresent(renderer);
    }
    SDL_StopTextInput();
    SDL_RemoveTimer( timerID );
    //Clean up
    cleanup(image, renderer, window);
    TTF_Quit();
    SDL_Quit();
}