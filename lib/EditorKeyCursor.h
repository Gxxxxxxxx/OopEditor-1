/*
 * This class is used for render editor keyboard cursor.
 */
#ifndef EDITORKEYCURSOR_LIBRARY_H
#define EDITORKEYCURSOR_LIBRARY_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include <iostream>

class EditorKeyCursor{
public:
    /*
     * Initialization construction
     * @param w The width of cursor
     * @param r The row position of cursor
     * @param c The column position of cursor
     * @param chw The character width
     * @param chh The character height
     * @param ls The space between lines
     * @param dis The space between cursor and character
     * @param v The cursor visibility
     */
    EditorKeyCursor(unsigned w = 3, unsigned r = 0, unsigned c = 0, unsigned chw=32, unsigned chh=65,
                 unsigned ls=10, unsigned dis = 5,bool v = true):
            cursorWidth(w),cursorHeight(chh),row(r),col(c),chWidth(chw),
            chHeight(chh),lineSpacing(ls),disBetweenChAndCursor(dis),visable(v){};
    /*
     * When cursor move,it is vital to update x,y
     */
    inline void calcCoordinate();

    /*
     * Move cursor forward.
     */
    inline void moveForward();

    /*
     * Move cursor backward.
     */
    inline void moveBackward();

    /*
     * Chande the visibility of cursor.
     */
    inline void changeVisibility();

    /*
     * Return whether the cursor is visible.
     */
    inline bool isVisable();

    /*
     * Return a SDL_Rect * object to draw a cursor.
     */
    SDL_Rect * getCursorRect();

    /*
     * Return x coordinate of cursor
     */
    inline int get_x();

    /*
     * Return y coordinate of cursor
     */
    inline int get_y();

    /*
     * Return cursor width
     */
    inline int get_cursorWidth();

    /*
     * Return cursor height
     */
    inline int get_cursorHeight();

private:
    bool visable;
    int cursorWidth;
    int cursorHeight;
    unsigned row;
    unsigned col;
    //The coordinate of cursor in the window.
    int x,y;
    unsigned chWidth;
    unsigned chHeight;
    unsigned disBetweenChAndCursor;
    unsigned lineSpacing;
};

/*
 * When cursor move,it is vital to update x,y
 */
inline void EditorKeyCursor::calcCoordinate() {
    x = col * chWidth + disBetweenChAndCursor; y = row * (lineSpacing + chHeight);
}

/*
 * Move cursor forward.
 */
inline void EditorKeyCursor::moveBackward() {
    --col;
    calcCoordinate();
}

/*
 * Move cursor backward.
 */
inline void EditorKeyCursor::moveForward() {
    ++col;
    calcCoordinate();
}

/*
 * Chande the visibility of cursor.
 */
inline void EditorKeyCursor::changeVisibility() {
    visable = !visable;
}

/*
 * Return whether the cursor is visible.
 */
inline bool EditorKeyCursor::isVisable() {
    return visable;
}

/*
 * Return x coordinate of cursor
 */
inline int EditorKeyCursor::get_x() {
    return x;
}

/*
 * Return y coordinate of cursor
 */
inline int EditorKeyCursor::get_y() {
    return y;
}

/*
 * Return cursor width
 */
inline int EditorKeyCursor::get_cursorWidth() {
    return cursorWidth;
}

/*
 * Return cursor height
 */
inline int EditorKeyCursor::get_cursorHeight() {
    return cursorHeight;
}
#endif