/*
 * Used as main window of the OopEditor.
 */

#ifndef EDITORWINDOW_LIBRARY_H
#define EDITORWINDOW_LIBRARY_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <cstdio>
#include <string>
#include "cleanup.h"
#include "res_path.h"
#include "EditorKeyCursor.h"
#include "GapBuffer.h"

class EditorWindow{
private:

    GapBuffer gb;

    /* Parameter of window size. */
    const int SCREEN_WIDTH  = 644;
    const int SCREEN_HEIGHT = 480;
    const int CHARACTERS_PER_ROW = 40;
    const int LineSpacing = 35;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_TimerID timerID;

    /* Color used for characters  */
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Color backColor = {39,40,34,255};
    SDL_Color cursorColor = { 255, 255, 255, 255};

    /* Default TTF file */
    const char * TTF_file = "../simhei.ttf";

    /* Keyboard cursor */
    EditorKeyCursor cursor;

    SDL_Event e;
    bool quit = false;



    /*
     * Log an SDL error with some error message to the output stream of our choice
     * @param os The output stream to write the message too
     * @param msg The error message to write, format will be msg error: SDL_GetError()
     */
    void logSDLError(std::ostream &os, const std::string &msg);

    /*
     * Draw an SDL_Texture to an SDL_Renderer at some destination rect
     * taking a clip of the texture if desired
     * @param tex The source texture we want to draw
     * @param rend The renderer we want to draw too
     * @param dst The destination rectangle to render the texture too
     * @param clip The sub-section of the texture to draw (clipping rect)
     *		default of nullptr draws the entire texture
     */
    void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr);

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
    void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr);

    /*
     * Render the message we want to display to a texture for drawing
     * @param message The message we want to display
     * @param fontFile The font we want to use to render the text
     * @param color The color we want the text to be
     * @param fontSize The size we want the font to be
     * @param renderer The renderer to load the texture in
     * @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
     */
    SDL_Texture* renderText(const std::string &message, const std::string &fontFile, SDL_Color color,
                            int fontSize, SDL_Renderer *renderer);

    /*
     * Render the character we want to display
     * @param ch The Character we want to display
     * @param fontFile The font we want to use to render the text
     * @param color The color we want the text to be
     * @param fontSize The size we want the font to be
     * @param renderer The renderer to load the texture in
     * @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
     */
    SDL_Texture* renderCh(const char ch, const std::string &fontFile, SDL_Color color, int fontSize,
                            SDL_Renderer *renderer);

    /*  There is no need for a copy construction function. */
    EditorWindow(const EditorWindow &);

public:
    /* Construction function */
    EditorWindow();
    /* Decomposition function*/
    ~EditorWindow();

    /*
     * Display the window.
     */
    void show();
};

/*
 * Used for cursor flash implement.
 */
Uint32 my_callbackfunc(Uint32 interval, void *param);

#endif