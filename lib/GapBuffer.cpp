#include "GapBuffer.h"

#include <iostream>
#include <fstream>
#include <string>

void GapBuffer::InitBuffer(unsigned int size){

    /* we can't initialize within construction list*/
    GAP_BUFFER_SIZE = size;

    if(text)
        delete[] text;

    text = new char[GAP_BUFFER_SIZE];

    if(!text){
        throw std::runtime_error("There is no enough space.");
    }

    textEnd = text + size;
    gapStart = text;
    gapEnd = textEnd;
    cursor = text;
}


/*
 * Initialization of Gap Buffer
 */
GapBuffer::GapBuffer(int gsize):text(nullptr) {

    InitBuffer(gsize);
}

/*
 * Constructor with instantiating with an existing file.
 * 1.Get the file size;
 * 2.Initialize the buffer
 * 3.Text-->buffer
 */
GapBuffer::GapBuffer(char *filename) {

    std::ifstream in(filename,std::ios::binary | std::ios::ate);

    if(!in.is_open())
        throw std::runtime_error("Can't open this text file.");

    /* Set buffer size be twice size of file size. */
    unsigned int fileSize = in.tellg(),bufferSize = fileSize * 2;

    InitBuffer(bufferSize);

    in.seekg(0,std::ios::beg);
    in.read(text,fileSize);
    in.close();


}

/*
 * Expand the size of Gap Buffer by factor 2.
 */
void GapBuffer::ExpandBuffer() {

    GAP_BUFFER_SIZE *= 2;
    char * ntext = new char[GAP_BUFFER_SIZE];

    /* Copy the left part of the text */
    memcpy(ntext,text,gapStart-text);
    /* Copy the right part of the text */
    memcpy(ntext+(gapStart-text),gapEnd,textEnd-gapEnd);

    /* Remember the old place of cursor. */
    unsigned cursorOffset = CursorOffset();
    /* Remember the text size */
    unsigned textSize = size();

    delete [] text;
    text = ntext;
    textEnd = text + GAP_BUFFER_SIZE;

    gapStart = text + textSize;
    gapEnd = textEnd;

    SetCursor(cursorOffset);
}


/*
 * Deconstruction function of GapBuffer.
 */
GapBuffer::~GapBuffer() {

    if (text)
        delete [] text;
}


/*
 * Return size of text of GapBuffer.
 */
unsigned int GapBuffer::size() {

    return (textEnd - text) - (gapEnd - gapStart);
}

/*
* Return the size of gap.
 */
unsigned int GapBuffer::gap_size() {
    return gapEnd-gapStart;
}

/*
* Move the gap to the current position of the cursor.
* Because when we press left key or right key, the cursor would go but the gap would't.
* The effect of this function is to keep insertion of left part easy.
*/
void GapBuffer::GapUpdate() {

    /* Cursor is the begin of gap. */
    if(cursor == gapStart)
        return;

    if(cursor == gapEnd){
        cursor = gapStart;
        return;
    }

    if(cursor < gapStart){
        memcpy(gapEnd-(gapStart-cursor),cursor,gapStart-cursor);
        gapEnd -= gapStart - cursor;
        gapStart = cursor;
    }else{
        memcpy(gapStart,gapEnd,cursor-gapEnd);
        gapStart += cursor - gapEnd;
        gapEnd = cursor;
        cursor = gapStart;
    }
}

/*
 * Set cursor at offset position.
 * We need to put gap into our consideration.
 */
void GapBuffer::SetCursor(unsigned int offset) {

    cursor = text + offset;

    if(cursor > gapStart){
        cursor = cursor + (gapEnd - gapStart);
    }

    if(cursor > textEnd)
        cursor = textEnd;
}

/*
 * Return character the cursor is pointing to.
 * If point is inside the gap, the return the
 * first character outside the gap.
 */
char GapBuffer::GetChar() {

    if(cursor == gapStart)
        cursor = gapEnd;

    return *cursor;
}

/*
* Replace the character before cursor.
* Does not move the gap.
*/
void GapBuffer::ReplaceChar(char ch) {

    if(cursor == text)
        return;

    if(cursor == gapEnd)
        cursor = gapStart;

    *(cursor-1) = ch;
}

/*
* Insert a character at cursor position.
*/
void GapBuffer::InsertChar(char ch) {

    if(gap_size() < 1)
        ExpandBuffer();

    GapUpdate();
    *(cursor++) = ch;
    ++gapStart;
}

/*
* Delete a character at cursor position.
*/
void GapBuffer::DeleteChar() {

    //Set cursor at GapStart
    if(cursor < gapStart || cursor == gapEnd)
        GapUpdate();

    --cursor;
    --gapStart;
}

/*
 * Return offset of cursor.
 */
unsigned int GapBuffer::CursorOffset() {

    if(cursor > gapStart)
        return cursor - (gapEnd - gapStart) - text;
    else
        return cursor - text;
}

/*
 * Delete a string(length = dsize) from cursor.
 */
void GapBuffer::DeleteString(unsigned int dsize) {

    if(cursor != gapStart)
        GapUpdate();

    if(dsize > (cursor - text))
        throw std::runtime_error::runtime_error("There is no enough long string to delete");

    gapStart -= dsize;
    cursor -= dsize;
}


/*
 * Insert a string( s ) from cursor.
 */
void GapBuffer::InsertString(std::string s) {

    if(cursor != gapStart)
        GapUpdate();

    if(gap_size() < s.size()){
        ExpandBuffer();
    }

    /* We can not use memcpy here. */
    s.copy(cursor,s.size());

    cursor += s.size();
    gapStart += s.size();
}

/*
 * Move Cursor forward one character.
 */
void GapBuffer::CursorForward() {

    /* If cursor is the tail of buffer */
    if(cursor == textEnd)
        return;

    /* If cursor is at the end of left part of text
     * and there is no space in the right part*/
    if(cursor == gapStart && gapEnd == textEnd)
        return;

    /* If cursor at the end of left part of text,
     * moving cursor would put it into right part.*/
    if(cursor == gapStart)
        cursor = gapEnd;
    else
        cursor += 1;
}


/*
 * Move Cursor backward one character.
 */
void GapBuffer::CursorBackward() {

    /* If cursor is at the begin of text.*/
    if(cursor == text)
        return;

    /* If cursor is at the position of GapEnd*/
    if(cursor == gapEnd){
        if(gapStart == text)
            return;
        else
            cursor = gapStart - 1;
        return;
    }

    --cursor;
}

/*
 * Save text in the buffer to file.
 */
int GapBuffer::SaveBufferToFile(char *filename) {

    std::ofstream out(filename);

    if(!out)
        return 1;

    out.write(text,gapStart-text);
    out.write(gapEnd,textEnd-gapEnd);
    out.close();
    return 0;
}

/*
 * Output text in left part and right part.
 * Used for Debug
 */
void GapBuffer::Debug() {
    static int count = 0;
    ++count;
    GapUpdate();
    std::cout << "Debug case " << count << std::endl;
    std::cout << "cursor offset = " << CursorOffset() << std::endl;
    std::cout << "gapStart = " << (gapStart - text) << std::endl;
    std::cout << "gapEnd = " << (gapEnd - text) << std::endl;
    std::cout << "The left part is: " << std::endl;
    std::cout.write(text,cursor-text) << std::endl;
    std::cout << "The right part is: " << std::endl;
    std::cout.write(gapEnd,textEnd-gapEnd) << std::endl << std::endl;
}

/*
 * Move cursor forward i steps
 * @param i steps number
 */
void GapBuffer::CursorForwardByStep(unsigned i) {
    if(cursor < gapStart){
        if(cursor + i > gapStart)
            cursor += gapEnd - gapStart + i;
        else
            cursor += i;
    }
    else if(cursor == gapStart)
        cursor = gapEnd +i;
    else
        cursor += i;
}

/*
 * Move cursor backward i steps
 * @param i steps number
 */
void GapBuffer::CursorBackwardByStep(unsigned i) {
    if(cursor <= gapStart)
        cursor -= i;
    else if(cursor == gapEnd)
        cursor = gapStart - i;
    else{
        if(cursor - i < gapEnd)
            cursor -= gapEnd - gapStart + 1;
        else
            cursor -= i;
    }
}


