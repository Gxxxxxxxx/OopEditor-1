//
// Created by 缪征 on 2018/6/18.
//

//
// Created by 缪征 on 2018/6/17.
//

/* 这里库的导入存在问题，所以暂时先用include导入。。。。 */
#include "GapBuffer.h"
#include "GapBuffer.cpp"

int main(){
    //EditorWindow editor;
    //editor.show();
    ///std::cout << std::endl;
    GapBuffer gb;
    gb.InsertString("AAAA");
    gb.Debug();

    gb.CursorBackward();
    gb.Debug();

    gb.InsertString("BBBB");
    gb.Debug();

    gb.ReplaceChar('p');
    gb.Debug();

    gb.InsertChar('w');
    gb.CursorBackward();
    gb.Debug();

    gb.CursorBackwardByStep(3);
    gb.Debug();

    gb.CursorForwardByStep(2);
    gb.Debug();


    return 0;
}
