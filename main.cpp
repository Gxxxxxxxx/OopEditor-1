//
// Created by 缪征 on 2018/6/17.
//

#include "EditorWindow.h"
/* 这里SDL2库的导入存在问题，所以暂时先用include导入。。。。 */
#include "EditorWindow.cpp"

int main(){
    EditorWindow editor;
    editor.show();
    std::cout << std::endl;
    return 0;
}
