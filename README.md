Custom Text Editor in C++ — MyString & Raylib
Overview
This project is a custom text editor developed in C++. It was built to demonstrate string manipulation, dynamic memory management, data structures, cursor movement, and text editing.
The project has two implementations of the editor:
* Console-based version — included as commented code.
* Raylib-based graphical version — the active implementation.
Both versions use the same basic Document and MyString concepts, but they differ in how input and output are handled.

Features
* Custom MyString class instead of std::string
* Dynamic memory management
* Multiple document lines
* Character insertion
* Enter/new-line handling
* Backspace and Delete
* Cursor movement
* Tab and Shift + Tab
* Automatic word wrapping
* Line splitting and merging
* Line numbers
* Status bar
* Graphical rendering using Raylib
* Custom iterator implementation for MyString

Technologies Used
* C++
* Raylib
* Windows API for console functionality
* Dynamic memory using new and delete

Project Architecture
The project is mainly divided into two classes:
             Text Editor
                  ?
        ?????????????????????
        ?                   ?
    Document             MyString
        ?                   ?
        ?             String operations
        ?
   Editor operations
MyString
MyString is a custom implementation of a string using a dynamically allocated character array.
Instead of:
std::string text;
the project maintains:
char* Cs;
int size;
It provides operations such as:
* Length
* Character access
* Insert
* Substring
* Concatenation
* Search
* Replace
* Split
* Tokenize
* Trim
* Uppercase / lowercase
* Reverse
* String comparison
* Iterators
This class forms the foundation of the text editor.

Document Class
The Document class represents the actual text being edited.
A document is stored as a dynamic array of MyString pointers:
Lines
 ?
 ??? MyString ? "Hello World"
 ??? MyString ? "This is a text editor"
 ??? MyString ? "C++ Project"
The document also maintains the cursor position:
cr   // current row
cc   // current column

Text Editing Operations
Insert Character
Characters are inserted at the current cursor position. After insertion, the cursor moves forward.
Insert Line
When Enter is pressed, the current line is split into two parts:
Before:

Hello World


After pressing Enter:

Hello
 World
The Lines array is resized and the new line is inserted.
Backspace
Backspace removes the character before the cursor.
If the cursor is at the beginning of a line, the current line is merged with the previous line.
Delete
Delete removes the character after the cursor.
If the cursor is at the end of a line, the next line is merged with the current line.
Tab
Tab inserts four spaces.
Shift + Tab removes indentation spaces from the beginning of a line.

Cursor Navigation
The editor supports:
* Left
* Right
* Up
* Down
When moving between lines of different lengths, the cursor automatically adjusts if the current column does not exist on the destination line.

Word Wrapping
The editor automatically checks the length of the current line after inserting a character.
When a line exceeds approximately 70 characters, the editor searches backward for a space and splits the line there.
This produces more natural wrapping by attempting to keep complete words together.

Two Editor Implementations
1. Console Version
The original console-based implementation is present in the project as commented-out code.
It uses:
_kbhit()
_getch()
to detect keyboard input.
Console-related functionality is handled using the Windows API.
The helper functions include:
gotoRowCol()
color()
hideConsoleCursor()
This version displays the text directly in the Windows console.
Console Input Flow
Keyboard
   ?
_getch()
   ?
Document
   ?
Console output
The console version demonstrates how a text editor can be implemented without a graphical library.

2. Raylib Version
The active version uses Raylib to provide a graphical text-editing environment.
Raylib handles:
* Window creation
* Keyboard input
* Text rendering
* Cursor rendering
* Text measurement
* Frame updates
The editor starts with:
InitWindow(900, 700, "Text Editor");
SetTargetFPS(60);
The application then continuously processes keyboard input and redraws the document.
Raylib Input Flow
Keyboard
   ?
Raylib Input
   ?
Document
   ?
Raylib Rendering
   ?
Window

Graphical Interface
The Raylib version displays:
* Line numbers
* Document text
* Blinking cursor
* Current line
* Current column
* Total number of lines
* Insert mode status
The cursor's pixel position is calculated using Raylib's MeasureText() based on the text before the cursor.

Dynamic Memory Management
Dynamic memory is an important part of the project.
MyString dynamically allocates its character array:
new char[size + 1]
The Document dynamically allocates its array of lines:
new MyString*[numLines]
Whenever a line is added or removed, a new pointer array is created and the old array is released.
This project therefore demonstrates:
* new
* new[]
* delete
* delete[]
* Deep copying
* Pointer management
* Dynamic array resizing

Iterator Support
The custom MyString class also implements an iterator.
It supports operations such as:
begin()
end()
Find()
FindFrom()
SubstrIter()
InsertAt()
EraseRange()
This allows characters to be traversed and manipulated using iterator positions rather than only integer indexes.

Project Structure
A typical structure is:
TextEditor/
?
??? main.cpp
??? Document.h
??? Document.cpp
??? BSAI25066-MyString.h
??? BSAI25066-MyString.cpp
??? Helper.h
??? README.md
main.cpp
Starts the text editor.
Document.cpp / Document.h
Contains the document and editor functionality.
MyString.cpp / MyString.h
Contains the custom string implementation and iterator.
Helper.h
Contains Windows console helper functions used by the console implementation.

Concepts Demonstrated
This project demonstrates several important C++ concepts:
* Object-Oriented Programming
* Classes and objects
* Constructors and destructors
* Dynamic memory allocation
* Pointers
* Dynamic arrays
* Deep copying
* String manipulation
* Iterators
* Searching algorithms
* Text editing algorithms
* Keyboard input handling
* Graphical rendering
* Event loops

Future Improvements
Possible extensions include:
* File opening and saving
* Undo / Redo
* Copy and Paste
* Text selection
* Mouse-based cursor positioning
* Scrolling
* Find and Replace interface
* Syntax highlighting
* Multiple documents/tabs
* Improved memory management using STL containers

Conclusion
This project implements a text editor from the ground up using a custom MyString class and a Document class.
The project contains two approaches to the user interface: an earlier console-based implementation, preserved in commented code, and the active Raylib graphical implementation.
The custom MyString class handles the low-level string operations and dynamic character storage, while Document manages multiple lines, cursor movement, editing operations, and word wrapping.
The Raylib version builds a graphical interface on top of this functionality, demonstrating how custom data structures can be combined with a graphics library to create a functional application.

