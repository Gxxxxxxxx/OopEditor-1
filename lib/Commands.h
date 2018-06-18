/*
 * This library is used for implementation of Undo/Redo Framework.
 */

#ifndef COMMANDS_LIBRARY_H
#define COMMANDS_LIBRARY_H

#include <iostream>
#include <stack>

/* command type definition */
enum class COMMANDTYPE{INSERTCH,DELETECH,INSERTSTRING,DELETESTRING};

class Command{
private:
    COMMANDTYPE type;
    unsigned int actionPosition;    //cursor position when this action happend
    unsigned int l;                 //used to record string(insertString && deleteString) length
    char * content;                   //used to store string being manipulated.
public:
    friend class Commands;
    /* Construction function */
    Command();
    /*
     * Decomposition function.
     * In order to know whether we allocate space for content,
     * we have to initilize content with nullptr(c11 feature).
     * In this function, We have to free the space in content(char *).
     */
    ~Command();
};

class Commands{
private:
    std::stack<Command> redoStack,undoStack;
public:
    /* Constuction function */
    Commands();
    /* Decomposition function */
    ~Commands();


    /*
     * When one command is executed,we have to put this command into undo stack.
     * @param c The command which would be inserted.
     */
    void InsertCommand(const Command & c);

    /*
     * Redo action.
     * Pop one command from redo stack,and parse it.
     * Finally push it into undo stack.
     * If Redo succeeds,return true else return false/
     */
    bool redo();

    /*
     * Pop one command from undo stack,and parse it.
     * Finally push it into redo stack.
     * If undo succeeds,return true else return false.
     */
    bool undo();

};

#endif