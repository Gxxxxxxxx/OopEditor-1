# Introduction

​	简易文本编辑器（源代码编辑器，目前阶段不考虑富文本），目前仅仅是源代码编辑器。

# Features

Waiting...

# Structure

### Text Storage(文本模型)

* Gap buffer
  * https://en.wikipedia.org/wiki/Gap_buffer

### Text Container(排版引擎)

​	目前阶段，固定layout，包括如下

* 设置相同的行高
* 固定字体和字体大小
* 不支持窗口缩放
* 不支持窗口滚动
* 单窗口

### Text View (显示引擎)

* 编辑器窗口仅仅支持键盘输入

# Dependency

* Qt5.11
* SDL2
* FreeType(Waiting...)

# Tasks

* Qt widget类设计(作为外壳)

  * Menu Bar(signal槽不需要配置)
    * 文件加载
  * Tool Bar(signal槽不需要配置，按钮图片找一下)
    * save
    * undo
    * redo

* SDL windows类设计(@blacksmith96)

  * 键盘输入

    * 文本输入
    * 文本删除

  * Render text

    * 作为一个class static method(可以改变)

  * 文本结构暂时定为

    ```
    struct TEXT {
        std::string content;
        int cursor;
    }
    ```

### 未来

Waiting...

# Reference

### Overview

* 怎么去实现一个简单文本编辑器？ - luikore的回答 - 知乎
  https://www.zhihu.com/question/24328297/answer/108235629

* *The Craft of Text Editing*

  http://www.finseth.com/craft/

### Overview

* 《Qt学习之路2》

  https://www.devbean.net/2012/08/qt-study-road-2-catelog/

* SDL2

  https://www.libsdl.org

### Text Storage

暂缓

# 任务认领方法

* 每次开发前必须*Pull*!!!


* 在*Tasks*一栏对应任务右边写上自己姓名，实例:*task1(@blacksmith96)*，认领了任务之后需要负责下面所有的子任务（当然可以先子任务）。如果编写一个全新的类和方法，先在*docs*文件下创建相关文档。
  * 一个任务不限于一个人
* 以最小单位代码commit并编写测试（可以空缺），commit时候进行必要文字说明。
* 提交的代码务必是能编译通过的
* 小心*Merge*!!!

