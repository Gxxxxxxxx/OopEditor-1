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
    Command(){}
    
    /*
     * Decomposition function.
     * In order to know whether we allocate space for content,
     * we have to initilize content with nullptr(c11 feature).
     * In this function, We have to free the space in content(char *).
     */
    virtual ~Command(){
	while(false == undoStack.empty() )         //free the space in undoStack 
	{
			delete undoStack.top();
			undoStack.pop();
	}
	while(false == redoStack.empty() )            //free the space in redoStack 
		{
			delete redoStack.top();
			redoStack.pop();
		}
	}
};

class Commands{
private:
    std::stack<Command> redoStack,undoStack;
public:
    /* Constuction function */
    Commands(){}
    /* Decomposition function */
    ~Commands(){}


    /*
     * When one command is executed,we have to put this command into undo stack.
     * @param c The command which would be inserted.
     */
    void InsertCommand(const Command & c){
    Command *orign;
    COMMANDTYPE type=static_cast<COMMANDTYPE>;
    unsigned int actionPosition;    
    unsigned int l;                 
    char * content;
	
	orign = undoStack.top();
	undoStack.push(content);
	undoStack.push(l);
	undoStack.push(actionPosition);
	undoStack.push(type);
}
	
    

    /*
     * Redo action.
     * Pop one command from redo stack,and parse it.
     * Finally push it into undo stack.
     * If Redo succeeds,return true else return false/
     */
    bool redo(){
    	Command *orign;
        COMMANDTYPE type=static_cast<COMMANDTYPE>;
        unsigned int actionPosition;    
        unsigned int l;                 
        char * content;
        
		if( redoStack.empty() ) 
		return 1; 
		
		if(type==INSERTCH)  type=DELETECH;
        if(type==DELETECH)  type=INSERTCH; 
		if(type==INSERTSTRING)  type=DELETESTRING;
		if(type==DELETESTRING)  type=INSERTSTRING;
		
		orign = redoStack.top();
		redoStack.pop();
		undoStack.push( orign );
		redoStack.pop();
		undoStack.push( type ); 
		redoStack.pop(); 
		undoStack.push( actionPosition );
		redoStack.pop();            
		undoStack.push( l );
		redoStack.pop();                
		undoStack.push( content );          
}

    /*
     * Pop one command from undo stack,and parse it.
     * Finally push it into redo stack.
     * If undo succeeds,return true else return false.
     */
    bool undo(){
    	Command *orign;
        COMMANDTYPE type=static_cast<COMMANDTYPE>;
        unsigned int actionPosition;    
        unsigned int l;                 
        char * content;

		if( mUndo.size() < 2 )            //no space can be undoed 
			return 1;

		if(type==INSERTCH)  type=DELETECH;
		if(type==DELETECH)  type=INSERTCH; 
		if(type==INSERTSTRING)  type=DELETESTRING;
		if(type==DELETESTRING)  type=INSERTSTRING;

		orign = undoStack.top();
		undoStack.pop();
		redoStack.push( orign );
		undoStack.pop();
		redoStack.push( type ); 
		undoStack.pop(); 
		redoStack.push( actionPosition );
		undoStack.pop();            
		redoStack.push( l );
		undoStack.pop();                
		redoStack.push( content );
		
    }
    

};

#endif
