//#include "Helper.h"
//#include "Document.h"
//#include <iostream>
//#include <conio.h>
//#include <windows.h>
//
//using namespace std;
//
//Document::Document()
//{
//	numLines = 1;
//	Lines = new MyString * [numLines];
//	Lines[0] = new MyString("");
//	cr = 0;
//	cc = 0;
//}
//
//Document::~Document()
//{
//	for (int i = 0; i < numLines; i++) {
//		delete Lines[i];
//	}
//	delete[] Lines;
//}
//
//void Document::insertCharacter(char ch)
//{
//	Lines[cr]->insert(cc, ch);
//	cc++;
//	printLine();
//}
//
//void Document::insertLine()
//{
//	MyString leftPart = Lines[cr]->Substring(0, cc);
//	MyString *rightPart=nullptr;
//	if (cc < Lines[cr]->length()) {
//		rightPart = new MyString(Lines[cr]->Substring(cc, Lines[cr]->length() - cc));
//	}
//	else {
//		rightPart = new MyString("");
//	}
//	delete Lines[cr];
//	Lines[cr] = new MyString(leftPart);
//
//	MyString** newLines = new MyString * [numLines + 1];
//
//	for (int i = 0; i <= cr; i++) {
//		newLines[i] = Lines[i];
//	}
//	newLines[cr + 1] = rightPart;
//	for (int i = cr + 1; i < numLines; i++) {
//		newLines[i + 1] = Lines[i];
//	}
//	delete[] Lines;
//	Lines = newLines;
//	numLines++;
//	cr++;
//	cc = 0;
//
//	printDoc();
//}
//void Document::printDoc() {
//	system("cls");
//	for (int i = 0; i < numLines; i++) {
//		gotoRowCol(i, 0);
//		cout << Lines[i]->c_str();
//	}
//	gotoRowCol(cr, cc);
//}
//void Document::printLine() {
//	gotoRowCol(cr, 0);
//	cout << Lines[cr]->c_str() << " ";
//	gotoRowCol(cr, cc);
//}
//
//void Document::Run()
//{
//	printDoc();
//
//	while (true) {
//		if (_kbhit()) {
//			int ch = _getch();
//			if (ch == 13) {
//				insertLine();
//			}
//			else if (ch >= 32 and ch <= 126) {
//				insertCharacter((char)ch);
//			}
//		}
//	}
//
//}
//


#include "Document.h"

Document::Document()
{
    numLines = 1;
    Lines = new MyString * [numLines];
    Lines[0] = new MyString("");
    cr = 0;
    cc = 0;
}

Document::~Document()
{
    for (int i = 0; i < numLines; i++) {
        delete Lines[i];
    }
    delete[] Lines;
}

void Document::moveLeft()
{
    if (cc > 0) {
        cc--;
    }
    else if (cr > 0) {
        cr--;
        cc = Lines[cr]->length();
    }
}

void Document::moveRight()
{
    if (cc < Lines[cr]->length()) {
        cc++;
    }
    else if (cr < numLines - 1) {
        cr++;
        cc = 0;
    }
}

void Document::moveUp()
{
    if (cr > 0) {
        cr--;
        if (cc > Lines[cr]->length()) {
            cc = Lines[cr]->length();
        }
    }
}

void Document::moveDown()
{
    if (cr < numLines - 1) {
        cr++;
        if (cc > Lines[cr]->length()) {
            cc = Lines[cr]->length();
        }
    }
}

void Document::insertCharacter(char ch) {
    Lines[cr]->insert(cc, ch);
    cc++;
    checkWordWrap();
}

void Document::checkWordWrap()
{
    if (Lines[cr]->length() > 70) {
        int splitIndex = -1;

        for (int i = 70; i >= 0; i--) {
            if (Lines[cr]->CharacterAt(i) == ' ') {
                splitIndex = i;
                break;
            }
        }
        if (splitIndex == -1) {
            splitIndex = 70;
        }

        MyString leftPart = Lines[cr]->Substring(0, splitIndex);
        MyString rightPart = Lines[cr]->Substring(splitIndex + 1, Lines[cr]->length() - splitIndex - 1);

        delete Lines[cr];
        Lines[cr] = new MyString(leftPart);

        if (cr == numLines - 1) {
            MyString** newLines = new MyString * [numLines + 1];
            for (int i = 0; i <= cr; i++) {
                newLines[i] = Lines[i];
            }
            newLines[cr + 1] = new MyString(rightPart);
            delete[] Lines;
            Lines = newLines;
            numLines++;
        }
        else {
            MyString temp = rightPart.Concat(MyString(" ")).Concat(*Lines[cr + 1]);
            delete Lines[cr + 1];
            Lines[cr + 1] = new MyString(temp);
        }

        if (cc > splitIndex) {
            cc = cc - splitIndex - 1;
            cr++;
        }
    }
}

void Document::insertLine()
{
    MyString leftPart = Lines[cr]->Substring(0, cc);
    MyString* rightPartPtr = nullptr;
    if (cc < Lines[cr]->length()) {
        rightPartPtr = new MyString(Lines[cr]->Substring(cc, Lines[cr]->length() - cc));
    }
    else {
        rightPartPtr = new MyString("");
    }

    delete Lines[cr];
    Lines[cr] = new MyString(leftPart);

    MyString** newLines = new MyString * [numLines + 1];
    for (int i = 0; i <= cr; i++) {
        newLines[i] = Lines[i];
    }

    newLines[cr + 1] = rightPartPtr;
    for (int i = cr + 1; i < numLines; i++) {
        newLines[i + 1] = Lines[i];
    }

    delete[] Lines;
    Lines = newLines;
    numLines++;
    cr++;
    cc = 0;
}

void Document::removeCharacter()
{
    if (cc > 0) {
        MyString left = Lines[cr]->Substring(0, cc - 1);
        MyString right = Lines[cr]->Substring(cc, Lines[cr]->length() - cc);
        delete Lines[cr];
        Lines[cr] = new MyString(left.Concat(right));
        cc--;
    }
    else if (cr > 0) {
        int prevLen = Lines[cr - 1]->length();
        MyString merged = Lines[cr - 1]->Concat(*Lines[cr]);
        delete Lines[cr - 1];
        Lines[cr - 1] = new MyString(merged);

        MyString** newLines = new MyString * [numLines - 1];
        for (int i = 0; i < cr; i++) {
            newLines[i] = Lines[i];
        }
        for (int i = cr + 1; i < numLines; i++) {
            newLines[i - 1] = Lines[i];
        }

        delete Lines[cr];
        delete[] Lines;
        Lines = newLines;
        numLines--;
        cr--;
        cc = prevLen;
    }
}

void Document::deleteCharacter()
{
    if (cc < Lines[cr]->length()) {
        MyString left = Lines[cr]->Substring(0, cc);
        MyString right = Lines[cr]->Substring(cc + 1, Lines[cr]->length() - cc - 1);
        delete Lines[cr];
        Lines[cr] = new MyString(left.Concat(right));
    }
    else if (cr < numLines - 1) {
        MyString merged = Lines[cr]->Concat(*Lines[cr + 1]);
        delete Lines[cr];
        Lines[cr] = new MyString(merged);

        MyString** newLines = new MyString * [numLines - 1];
        for (int i = 0; i <= cr; i++) {
            newLines[i] = Lines[i];
        }
        for (int i = cr + 2; i < numLines; i++) {
            newLines[i - 1] = Lines[i];
        }

        delete Lines[cr + 1];
        delete[] Lines;
        Lines = newLines;
        numLines--;
    }
}

void Document::insertTab()
{
    for (int i = 0; i < 4; i++) {
        insertCharacter(' ');
    }
}

void Document::removeTab()
{
    if (cc == 0 and Lines[cr]->length() > 0 and Lines[cr]->CharacterAt(0) == ' ') {
        int spacesToRemove = 0;
        while (spacesToRemove < 4 and Lines[cr]->CharacterAt(spacesToRemove) == ' ') {
            spacesToRemove++;
        }

        MyString right = Lines[cr]->Substring(spacesToRemove, Lines[cr]->length() - spacesToRemove);
        delete Lines[cr];
        Lines[cr] = new MyString(right);
    }
}

void Document::Draw()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int fontSize = 20;
    int padWidth = 50;
    int statusBarHeight = 30;
    int startX = padWidth + 10;
    int startY = 10;

    for (int i = 0; i < numLines; i++) {
        int lineY = startY + (i * fontSize);
        DrawText(TextFormat("%d", i + 1), 10, lineY, fontSize, DARKGRAY);
        DrawText(Lines[i]->c_str(), startX, lineY, fontSize, BLACK);
    }

    MyString textBeforeCursor = Lines[cr]->Substring(0, cc);
    int cursorPixelX = startX + MeasureText(textBeforeCursor.c_str(), fontSize);
    int cursorPixelY = startY + (cr * fontSize);

    if ((int)(GetTime() * 2) % 2 == 0) {
        DrawRectangle(cursorPixelX, cursorPixelY, 2, fontSize, BLACK);
    }

    DrawRectangle(0, screenHeight - statusBarHeight, screenWidth, statusBarHeight, DARKGRAY);
    DrawText("INSERT MODE", 10, screenHeight - statusBarHeight + 5, 20, WHITE);
    DrawText(TextFormat("Ln %d, Col %d", cr + 1, cc + 1), 200, screenHeight - statusBarHeight + 5, 20, WHITE);
    DrawText(TextFormat("Total Lines: %d", numLines), screenWidth - 160, screenHeight - statusBarHeight + 5, 20, WHITE);
}

void Document::Run()
{
    InitWindow(900, 700, "Text Editor");
    SetTargetFPS(60);
    SetTextLineSpacing(20);

    while (!WindowShouldClose()) {

        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) and (key <= 125)) {
                insertCharacter((char)key);
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_ENTER)) {
            insertLine();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            removeCharacter();
        }
        if (IsKeyPressed(KEY_DELETE)) {
            deleteCharacter();
        }
        if (IsKeyPressed(KEY_TAB)) {
            if (IsKeyDown(KEY_LEFT_SHIFT) or IsKeyDown(KEY_RIGHT_SHIFT)) {
                removeTab();
            }
            else {
                insertTab();
            }
        }

        if (IsKeyPressed(KEY_LEFT)) {
            moveLeft();
        }

        if (IsKeyPressed(KEY_RIGHT)) {
            moveRight();
        }

        if (IsKeyPressed(KEY_UP)) {
            moveUp();
        }

        if (IsKeyPressed(KEY_DOWN)) {
            moveDown();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        Draw();
        EndDrawing();
    }
    CloseWindow();
}