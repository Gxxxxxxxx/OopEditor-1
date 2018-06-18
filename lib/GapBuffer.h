/*
 *  gap_buffer.h
 *
 *  A text buffer class using the buffer-gap technique for managing
 *  the text stored in the buffer.
 *
 *  This following example explains how this gap buffer works.
 *   Hello w[.....]orld!
 *  👆->text            👆->textEnd
 *  '['->gapStart
 *  ']'->gapEnd
 */


#ifndef GAPBUFFER_LIBRARY_H
#define GAPBUFFER_LIBRARY_H

#include <iostream>
#include <string>

class GapBuffer{
public:

private:
    char * cursor;
    char * text;
    char * textEnd;
    char * gapStart;
    char * gapEnd;

    unsigned int GAP_BUFFER_SIZE;

    /*
     * Initialize the gap buffer with size.
     * @param size The size of buffer
     */
    void InitBuffer(unsigned int size);

    /*
     * Expand the size of buffer when the space of buffer is not enough
     * Usually we expand the size of buffer by factor 2.
     */
    void ExpandBuffer(void);

    /* There is no need for Copy construction. */
    GapBuffer(const GapBuffer& gb);

public:
    static const int DEFAULT_GAP_BUFFER_SIZE = 20;

    /* Constructor with default gap size.
     * @param gsize The size of buffer.
     */
    GapBuffer(int gsize = DEFAULT_GAP_BUFFER_SIZE);

    /* Constructor with instantiating with an existing file.
     * @param filename The name of text file.
     */
    GapBuffer(char * filename);

    ~GapBuffer();

    /*
     * Return the size of real text(buffer size minus gap size).
     */
    inline unsigned int size();

    /*
     * Return the size of gap.
     */
    inline unsigned int gap_size();

    /*
     * Move the gap to the current position of the cursor.
     * Because when we press left key or right key, the cursor would go but the gap would't.
     */
    void GapUpdate();

    /*
     * Set point to offset from start of buffer.
     * When we press up key or down key cursor would go to next line or the line before the current line.
     * @param offset The offset of cursor you want to set.
     */
    void SetCursor(unsigned int offset);

    /*
     * Return the size of gap.
     */
    unsigned int CursorOffset();

    /*
     * Return character that cursor is pointing to.
     * If point is inside the gap, then return the
     * first character outside the gap.
     */
    char GetChar();

    /*
     * Replace the character of cursor.
     * Does not move the gap.
     * @param ch The character you want to use to replace.
     */
    void ReplaceChar(char ch);

    /*
     * Insert a character at cursor position.
     * @param ch The character you want to insert.
     */
    void InsertChar(char ch);

    /*
     * Delete a character at cursor position.
     */
    void DeleteChar();

    /*
     * Insert a string at cursor position.
     * @param s The string you want to insert.
     */
    void InsertString(std::string s);

    /*
     * Delete the string following the cursor.
     * This function used when we select a area of text and delete it.
     * This process is completed in 2 steps.
     * Step1: Move the cursor right before the area.
     * Step2: Delete the text following the cursor.
     * @param desize The number of characters you want to delete.
     */
    void DeleteString(unsigned int dsize);

    /*
     * Save text content into file.
     * @param filename The name of text file.
     */
    int SaveBufferToFile(char * filename);

    /*
     * Move Cursor forward one character.
     */
    void CursorForward();

    /*
     * Move Cursor backward one character.
     */
    void CursorBackward();

    /*
     * Move cursor forward i steps
     * @param i steps number
     */
    void CursorForwardByStep(unsigned i);

    /*
     * Move cursor backward i steps
     * @param i steps number
     */
    void CursorBackwardByStep(unsigned i);

    /*
     * Output text in left part and right part.
     */
    void Debug();
};
#endif