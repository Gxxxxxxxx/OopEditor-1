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
    EditorKeyCursor(unsigned w = 1, unsigned r = 0, unsigned c = 0, unsigned chw=16, unsigned chh=33,
                 unsigned ls=5, unsigned dis = 3,bool v = true):
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
    inline bool isVisable() const;

    /*
     * Return a SDL_Rect * object to draw a cursor.
     */
    SDL_Rect * getCursorRect();

    /*
     * Return x coordinate of cursor
     */
    inline int get_x() const;

    /*
     * Return y coordinate of cursor
     */
    inline int get_y() const;

    /*
     * Return cursor width
     */
    inline int get_cursorWidth() const;

    /*
     * Return cursor height
     */
    inline int get_cursorHeight() const;

    /*
     * Go to next line
     */
    inline void moveDown();

    /*
     * Go to the line before current line
     */
    inline void moveUp();

    /*
     * Go to new_r,new_c
     */
    inline void set(unsigned new_r, unsigned new_c);

    /*
     * Go back to the start of line.
     */
    inline void gotoLineHead();

    /*
     * Go to the tail of the line
     */
    inline void gotoLineTail();

    /*
     * Debug
     */
    inline void debug();

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
    if(col == 0){
        if(row > 0){
            --row;
            col = 39;
        }
        return;
    }
    else
        --col;
}

/*
 * Move cursor backward.
 */
inline void EditorKeyCursor::moveForward() {
    ++col;
    if(col == 40){
        col = 0;
        ++row;
    }
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
inline bool EditorKeyCursor::isVisable() const{
    return visable;
}

/*
 * Return x coordinate of cursor
 */
inline int EditorKeyCursor::get_x() const{
    return x;
}

/*
 * Return y coordinate of cursor
 */
inline int EditorKeyCursor::get_y() const{
    return y;
}

/*
 * Return cursor width
 */
inline int EditorKeyCursor::get_cursorWidth() const{
    return cursorWidth;
}

/*
 * Return cursor height
 */
inline int EditorKeyCursor::get_cursorHeight() const{
    return cursorHeight;
}

/*
 * Go to next line
 */
inline void EditorKeyCursor::moveDown() {
    ++row;
}

/*
 * Go to the line before current line
 */
inline void EditorKeyCursor::moveUp() {
    if(row > 0)
        --row;
}

/*
 * Set row and column.
 */
inline void EditorKeyCursor::set(unsigned new_r, unsigned new_c){
    row = new_r;
    col = new_c;
}

/*
 * Go to the start of line.
 */
inline void EditorKeyCursor::gotoLineHead() {
    col = 0;
}

/*
 * Go to the tail of the line.
 */
inline void EditorKeyCursor::gotoLineTail() {
    col = 40;
}

/*
 * Debug
 */
inline void EditorKeyCursor::debug() {
    std::cout << "row = " << row << " col= " << col << std::endl;
}
#endif