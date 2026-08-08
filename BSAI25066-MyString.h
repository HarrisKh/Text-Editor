#pragma once
#include <fstream>
#include <iostream>
using namespace std;
class MyString
{
	int size;
	char* Cs;
	MyString itos(int n) {
		int temp = n;
		int a = 0;
		while (n != 0) {
			n /= 10;
			a++;
		}
		size = a;
		int i = size;
		while (temp != 0) {
			Cs[i - 1] = (temp % 10) + '0';
			temp /= 10;
			i--;
		}
		return *this;

	}

	int Size(const char* ch)const {
		int i = 0;
		while (ch[i] != '\0') {
			i++;
		}
		return i;
	}
public:
	class Iterator {
		char* ptr;
	public:
		Iterator(char* p) :ptr(p) {}
		char& get() { return *ptr; }
		void next() { ptr++; }
		void prev() { ptr--; }
		bool equals(const Iterator& other) { return ptr == other.ptr; }
		bool notEquals(const Iterator& other) { return ptr != other.ptr; }
		void advance(int n) {
			if (n < 0)
				ptr -= n;
			else
				ptr += n;
		}
		int distanceTo(const Iterator& other) { return other.ptr - this->ptr; }
	};
	Iterator begin();
	Iterator end();
	MyString();
	MyString(char c);
	MyString(const char* p);
	MyString(int n, char c);
	MyString(int num);
	MyString(ifstream& file);
	MyString(const MyString& other);
	~MyString();

	void print()const;
	int length()const;
	char CharacterAt(int i) const;
	void ReplaceAt(int i, char c);
	void ReplaceFirst(char c);
	void ShallowCopy(const MyString& a);
	MyString ITOS(int n);
	int stoi() const;
	void Clear();

	MyString Trim() const;
	MyString ToUpper() const;
	MyString ToLower() const;
	MyString Reverse() const;
	int StrCmp(const char* s1, const char* s2)const;
	bool IsEqual(const MyString& M) const;
	bool IsLess(const MyString& M) const;
	bool IsGreater(const MyString& M) const;
	MyString Substring(int start, int len) const;
	int IndexOf(char c) const;
	int LastIndexOf(char c) const;
	bool Contains(const char* substr) const;
	MyString Concat(const MyString& other) const;
	MyString Replace(const char* old, const char* newStr) const;
	MyString* Split(char delim, int& count) const;
	MyString* Tokenize(const char* delimiters, int& count) const;

	MyString SubstrIter(Iterator start, Iterator end);
	void InsertAt(Iterator pos, const MyString& str);
	void EraseRange(Iterator start, Iterator end);
	Iterator Find(char c);
	Iterator FindFrom(Iterator start, char c);
	void insert(int pos, char ch);
	const char* c_str() const;
};