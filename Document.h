#pragma once
#include "BSAI25066-MyString.h"
//
//class Document {
//    MyString** Lines;
//    int numLines;
//    int cr;
//    int cc;
//
//public:
//    Document();
//    ~Document();
//
//    void insertCharacter(char ch);
//    void insertLine();
//    void printDoc();
//    void printLine();
//    void Run();
//};

#include "raylib.h"

class Document {
    MyString** Lines;
    int numLines;
    int cr;
    int cc;
    int totalMatch = 0;
    int matchK = 0;
public:
    Document();
    ~Document();

    void insertCharacter(char ch);
    void insertLine();
    void checkWordWrap();
    void removeCharacter();
    void deleteCharacter();
    void insertTab();
    void removeTab();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void Draw();
    void Run();
    void search(MyString s);
    void cutAndPaste(int c1,int r1,int c2,int r2);
};