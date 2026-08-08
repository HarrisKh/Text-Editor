# Custom Text Editor in C++ - MyString and Raylib

## Overview

This project is a custom text editor developed in C++.

The main purpose of the project is to implement a text editor using a custom `MyString` class instead of `std::string`, while also learning dynamic memory management, string manipulation, cursor movement, and graphical application development.

The project contains two versions of the editor:

1. Console-based version - included as commented code.
2. Raylib-based version - the active graphical implementation.

Both versions use the `MyString` and `Document` classes for the core text editing functionality.

---

## Features

* Custom `MyString` class
* Dynamic character-array based string storage
* Multiple document lines
* Character insertion
* New line insertion
* Backspace
* Delete
* Cursor movement
* Tab insertion
* Shift + Tab indentation removal
* Automatic word wrapping
* Line splitting
* Line merging
* Line numbers
* Status bar
* Blinking cursor
* Custom string iterators
* Console-based editor implementation
* Graphical editor using Raylib

---

## Technologies Used

* C++
* Raylib
* Windows API
* Dynamic memory allocation

---

# Project Structure

The project is mainly divided into two important classes.

```text
Text Editor
|
+-- Document
|   |
|   +-- Manages document lines
|   +-- Manages cursor
|   +-- Handles editing operations
|   +-- Handles keyboard input
|   +-- Handles rendering
|
+-- MyString
    |
    +-- Stores characters
    +-- Performs string operations
    +-- Provides iterators
```

Raylib is used by the graphical version to handle the window, keyboard input, and rendering.

---

# MyString Class

The `MyString` class is a custom implementation of a string.

Instead of using:

```cpp
std::string
```

the project uses a dynamically allocated character array:

```cpp
char* Cs;
int size;
```

The character array stores the actual string and includes a null terminator.

For example, the string:

```text
Hello
```

is stored conceptually as:

```text
H e l l o \0
```

The class manages this memory manually using `new` and `delete[]`.

---

## MyString Functionality

The custom string class provides several operations, including:

* Length calculation
* Character access
* Character replacement
* Character insertion
* Substring extraction
* String concatenation
* Searching
* String comparison
* Trimming
* Uppercase conversion
* Lowercase conversion
* Reversing
* String replacement
* Splitting
* Tokenization
* Integer to string conversion
* String to integer conversion

The class also contains a custom iterator implementation for traversing and modifying the string.

---

# Document Class

The `Document` class represents the text currently being edited.

The document stores multiple `MyString` objects using a dynamically allocated array of pointers.

Conceptually, the structure looks like:

```text
Lines
|
+-- MyString: "Hello World"
|
+-- MyString: "This is a text editor"
|
+-- MyString: "C++ Project"
```

The document also stores the current cursor position.

```cpp
int cr;
int cc;
```

Where:

* `cr` represents the current row.
* `cc` represents the current column.

---

# Document Initialization

When a `Document` object is created, it initially contains one empty line.

The cursor starts at:

```text
Row: 0
Column: 0
```

The destructor releases all dynamically allocated lines and then releases the array containing the line pointers.

---

# Text Insertion

## Insert Character

The `insertCharacter()` function inserts a character at the current cursor position.

After inserting the character, the cursor moves one position forward.

The editor then checks whether the line needs to be wrapped.

---

## Insert Line

When the user presses Enter, `insertLine()` is called.

The current line is divided into two parts:

```text
Before:

Hello World
     |

After:

Hello
 World
```

The left part remains on the current line and the right part becomes a new line.

The `Lines` array is resized to make space for the new line.

---

# Cursor Movement

The editor supports four directional movements:

* Left
* Right
* Up
* Down

## Move Left

If the cursor is not at the beginning of the line, the column is decreased.

If the cursor is already at the beginning and a previous line exists, the cursor moves to the end of the previous line.

## Move Right

If the cursor is not at the end of the line, the column is increased.

If the cursor is at the end of a line and another line exists, the cursor moves to the beginning of the next line.

## Move Up and Down

When moving vertically, the editor attempts to keep the same column.

If the destination line is shorter than the current column, the cursor is moved to the end of that line.

---

# Backspace

The `removeCharacter()` function handles the Backspace key.

If the cursor is inside a line, the character before the cursor is removed.

Example:

```text
Before:

Hello|

After:

Hell|
```

If the cursor is at the beginning of a line, the current line is merged with the previous line.

Example:

```text
Before:

Hello
World|

After:

HelloWorld|
```

---

# Delete

The `deleteCharacter()` function handles the Delete key.

If a character exists after the cursor, it is removed.

Example:

```text
Before:

Hello| World

After:

Hello|World
```

If the cursor is at the end of a line, the current line is merged with the next line.

---

# Tab Handling

The editor represents a tab using four spaces.

The `insertTab()` function simply inserts four spaces.

```text
Tab = "    "
```

The editor also supports Shift + Tab.

`removeTab()` removes up to four leading spaces when the cursor is at the beginning of a line.

---

# Word Wrapping

The editor automatically checks the length of the current line after inserting characters.

If the line becomes longer than approximately 70 characters, the editor attempts to wrap it.

The algorithm searches backward from the limit for a space.

This allows the editor to wrap at a word boundary instead of unnecessarily splitting a word.

If no space is found, the line is split at the character limit.

The right part is then moved to the next line.

---

# Console Version

The project originally contains a console-based version of the editor.

This implementation is present in the source code as commented code.

The console version uses functions such as:

```cpp
_kbhit()
_getch()
```

to detect keyboard input.

It also uses Windows console functions through `windows.h`.

The helper functions include:

```cpp
gotoRowCol()
color()
hideConsoleCursor()
```

These functions allow the program to control the console cursor, text color, and cursor visibility.

### Console Input Flow

```text
Keyboard
|
v
_getch()
|
v
Document
|
v
Console Output
```

The console version demonstrates how the same text-editing logic can work without a graphical library.

---

# Raylib Version

The active version of the project uses Raylib.

Raylib is responsible for:

* Creating the application window
* Reading keyboard input
* Drawing text
* Drawing the cursor
* Measuring text
* Updating the screen

The editor creates a window using:

```cpp
InitWindow(900, 700, "Text Editor");
```

and runs at:

```cpp
SetTargetFPS(60);
```

---

# Raylib Editor Loop

The main editor loop continuously performs two tasks:

1. Process keyboard input.
2. Draw the current document.

The general flow is:

```text
Start
|
v
Initialize Raylib
|
v
Read keyboard input
|
v
Modify Document
|
v
Draw Document
|
v
Repeat
|
v
Close Window
```

The loop continues until the user closes the window.

---

# Graphical Interface

The Raylib version displays:

* Line numbers
* Text
* Cursor
* Insert mode
* Current line
* Current column
* Total number of lines

For example:

```text
1   Hello World
2   This is my text editor
3   C++ Project
```

The cursor position is calculated using the text before the cursor and Raylib's `MeasureText()` function.

---

# Blinking Cursor

The cursor is drawn as a small rectangle.

The program uses Raylib's `GetTime()` function to periodically show and hide the cursor.

This creates a blinking cursor similar to a normal text editor.

---

# Status Bar

The bottom of the editor contains a status bar.

It displays information such as:

```text
INSERT MODE

Ln 2, Col 10

Total Lines: 5
```

This allows the user to see their current position in the document.

---

# MyString Iterators

The custom `MyString` class also implements its own iterator.

The iterator provides functionality such as:

```cpp
begin()
end()
next()
get()
notEquals()
distanceTo()
```

The iterator can be used for searching, extracting substrings, inserting text, and removing ranges.

Functions such as:

```cpp
Find()
FindFrom()
SubstrIter()
InsertAt()
EraseRange()
```

use this iterator functionality.

This was implemented to understand how iterators work internally rather than relying entirely on STL iterators.

---

# Dynamic Memory Management

Dynamic memory management is one of the major concepts demonstrated by this project.

The `MyString` class dynamically allocates memory for its characters.

For example:

```cpp
Cs = new char[size + 1];
```

The memory is released using:

```cpp
delete[] Cs;
```

The `Document` class also dynamically allocates an array of `MyString` pointers.

When lines are added or removed, a new pointer array is allocated and the old array is deleted.

This demonstrates:

* `new`
* `new[]`
* `delete`
* `delete[]`
* Pointers
* Dynamic arrays
* Deep copying
* Manual memory management

---

# Project Files

A typical project structure is:

```text
TextEditor/
|
+-- main.cpp
+-- Document.h
+-- Document.cpp
+-- MyString.h
+-- MyString.cpp
+-- Helper.h
+-- README.md
```

## main.cpp

Contains the small program used to start the editor.

## Document.h

Contains the declaration of the `Document` class.

## Document.cpp

Contains the implementation of the text editor.

## MyString.h

Contains the declaration of the custom `MyString` class and its iterator.

## MyString.cpp

Contains the implementation of the custom string operations.

## Helper.h

Contains Windows console helper functions used by the console implementation.

---

# Concepts Demonstrated

This project demonstrates several important C++ concepts:

* Object-oriented programming
* Classes and objects
* Constructors and destructors
* Pointers
* Dynamic memory
* Dynamic arrays
* Deep copying
* Character arrays
* String manipulation
* Iterators
* Searching algorithms
* Cursor management
* Keyboard input
* Graphical rendering
* Application loops

---

# Possible Improvements

The editor can be extended with features such as:

* File opening
* File saving
* Copy and paste
* Undo and redo
* Text selection
* Mouse-based cursor positioning
* Scrolling
* Find and replace
* Syntax highlighting
* Multiple files or tabs
* Improved memory management using STL containers

---

# Conclusion

This project is a custom text editor developed in C++ using a manually implemented `MyString` class and a `Document` class.

The project contains two versions of the editor. The first is a console-based implementation that uses Windows console functionality and keyboard input through `_getch()` and `_kbhit()`. This version is preserved in the code as commented functionality.

The second and active implementation uses Raylib to provide a graphical text editor. Raylib handles the window, keyboard input, rendering, text measurement, and cursor display, while the `Document` class continues to handle the actual text manipulation.

The project demonstrates how fundamental C++ concepts such as dynamic memory, pointers, classes, custom data structures, string manipulation, and iterators can be combined to build a functional application from scratch.
