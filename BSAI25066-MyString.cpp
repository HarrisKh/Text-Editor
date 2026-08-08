#include "BSAI25066-MyString.h"

MyString::Iterator MyString::begin()
{
	return Iterator(&Cs[0]);
}

MyString::Iterator MyString::end() {
	return Iterator(&Cs[size]);
}

MyString::MyString() {
	size = 0;
	Cs = new char[1];
	Cs[0] = '\0';
}

MyString::MyString(char c)
{
	size = 1;
	Cs = new char[2];
	Cs[0] = c;
	Cs[1] = '\0';
}

MyString::MyString(const char* p)
{
	size = Size(p);
	Cs = new char[size + 1];
	int i = 0;
	while (p[i] != '\0') {
		Cs[i] = p[i];
		i++;
	}
	Cs[size] = '\0';
}

MyString::MyString(int n, char c)
{
	size = n;
	Cs = new char[size + 1];
	for (int i = 0; i < size - 1; i++) {
		Cs[i] = c;
	}
	Cs[size] = '\0';
}

MyString::MyString(int num)
{
	int temp = num;
	int count = 0;
	while (num > 0) {
		count++;
		num /= 10;
	}
	size = count;
	Cs = new char[count + 1];
	itos(temp);
}

MyString::MyString(ifstream& file)
{
	char buffer[1000];
	if (file.getline(buffer, 1000)) {
		size = Size(buffer);
		Cs = new char[size + 1];
	}
	else {
		size = 0;
		Cs = new char[1];
		Cs[0] = '\0';
	}
}
MyString::MyString(const MyString& other)
{
	size = other.size;
	Cs = new char[size + 1];
	for (int i = 0; i < size; i++) {
		Cs[i] = other.Cs[i];
	}
	Cs[size] = '\0';
}



MyString::~MyString()
{
	delete[]Cs;
	Cs = nullptr;
}

void MyString::print()const
{
	for (int i = 0; i < size; i++) {
		cout << Cs[i];
	}
	cout << endl;
}

int MyString::length()const
{
	return size;
}

char MyString::CharacterAt(int i) const
{
	if (i > size or i <= 0)
		return '\0';
	return Cs[i];
}

void MyString::ReplaceAt(int i, char c)
{
	Cs[i] = c;
}

void MyString::ReplaceFirst(char c)
{
	Cs[0] = c;
}

void MyString::ShallowCopy(const MyString& a)
{
	this->size = a.size;
	this->Cs = a.Cs;
}

MyString MyString::ITOS(int n)
{
	char temp[20];
	int i = 0;
	int num = n;
	while (n > 0) {
		int d = n % 10;
		temp[i++] = d + '0';
		n /= 10;
	}
	temp[i] = '\0';
	for (int s = 0, end = i - 1; s < end; s++, end--) {
		char t = temp[s];
		temp[s] = temp[end];
		temp[end] = t;
	}
	return MyString(temp);
}

int MyString::stoi() const
{
	int i = 0, num = 0;
	for (; i < size; i++) {
		if (Cs[i] >= '0' and Cs[i] <= '9') {
			num = (num * 10) + (Cs[i] - '0');
		}
		else
			break;
	}
	return num;
}

void MyString::Clear()
{
	delete[] Cs;
	size = 0;
	Cs = new char[1];
	Cs[0] = '\0';
}

MyString MyString::Trim() const
{
	if (size == 0)
		return MyString("");
	int s = 0, e = size - 1;
	while (s < size and (Cs[s] == ' ' or Cs[s] == '\n' or Cs[s] == '\t')) {
		s++;
	}
	while (e >= s and (Cs[e] == ' ' or Cs[e] == '\n' or Cs[e] == '\t')) {
		e--;
	}
	int len = e - s + 1;
	if (len <= 0)
		return MyString("");

	char* temp = new char[len + 1];
	for (int i = 0; i < len; i++) {
		temp[i] = Cs[s + i];
	}
	temp[len] = '\0';

	MyString result(temp);
	delete[] temp;
	return result;
}

MyString MyString::ToUpper() const
{
	char* temp = new char[size + 1];
	for (int i = 0; i < size; i++) {
		if (Cs[i] >= 'a' and Cs[i] <= 'z') {
			temp[i] = Cs[i] - 32;
		}
		else {
			temp[i] = Cs[i];
		}
	}
	temp[size] = '\0';
	MyString result(temp);
	delete[] temp;
	return result;
}

MyString MyString::ToLower() const
{
	char* temp = new char[size + 1];
	for (int i = 0; i < size; i++) {
		if (Cs[i] >= 'A' and Cs[i] <= 'Z') {
			temp[i] = Cs[i] + 32;
		}
		else {
			temp[i] = Cs[i];
		}
	}
	temp[size] = '\0';
	MyString result(temp);
	delete[] temp;
	return result;
}

MyString MyString::Reverse() const
{
	char* temp = new char[size + 1];
	for (int i = 0; i < size; i++) {
		temp[i] = Cs[size - i - 1];
	}
	temp[size] = '\0';
	MyString result(temp);
	delete[]temp;
	return result;
}
int CompareStr(const char* s1, const char* s2) {
	while (*s1 and (*s1 == *s2)) {
		s1++;
		s2++;
	}
	return *(const char*)s1 - *(const char*)s2;
}
int MyString::StrCmp(const char* s1, const char* s2) const {
	int i = 0;
	while (true) {
		if (s1[i] != s2[i]) {
			if (s1[i] > s2[i])
				return 1;
			else
				return -1;
		}
		if (s1[i] == '\0') {
			return 0;
		}
		i++;
	}
}
bool MyString::IsEqual(const MyString& M) const {
	if (this->size != M.size)
		return false;
	return StrCmp(this->Cs, M.Cs) == 0;
}
bool MyString::IsLess(const MyString& M) const {
	return StrCmp(this->Cs, M.Cs) == -1;
}

bool MyString::IsGreater(const MyString& M) const {
	return StrCmp(this->Cs, M.Cs) == 1;
}

MyString MyString::Substring(int start, int len) const
{
	if (start + len > size)
		len = size - start;
	MyString temp;
	int j = 0;
	temp.size = len;
	temp.Cs = new char[len + 1];
	for (int i = start; i < len; i++) {
		temp.Cs[j++] = this->Cs[i];
	}
	temp.Cs[j] = '\0';
	return temp;
}

int MyString::IndexOf(char c) const
{
	for (int i = 0; i < size; i++) {
		if (Cs[i] == c)
			return i;
	}
	return 0;
}

int MyString::LastIndexOf(char c) const
{
	int last = -1;
	for (int i = 0; i < size; i++) {
		if (Cs[i] == c)
			last = i;
	}
	return last;
}

bool MyString::Contains(const char* substr) const
{
	int subLen = Size(substr);
	if (subLen > size)
		return false;
	for (int i = 0; i <= size - subLen; i++) {
		bool m = true;
		for (int j = 0; j < subLen; j++) {
			if (Cs[i + j] != substr[j]) {
				m = false;
				break;
			}
		}
		if (m)
			return true;
	}
	return false;
}

MyString MyString::Concat(const MyString& other) const
{
	MyString temp;
	temp.size = this->size + other.size;
	temp.Cs = new char[this->size + other.size + 1];
	for (int i = 0; i < this->size; i++) {
		temp.Cs[i] = this->Cs[i];
	}
	int j = 0;
	for (int i = this->size; i < this->size + other.size; i++) {
		temp.Cs[i] = other.Cs[j++];
	}
	temp.Cs[temp.size] = '\0';
	return temp;
}

MyString MyString::Replace(const char* old, const char* newStr) const
{
	int oldLen = Size(old);
	int newLen = Size(newStr);
	int count = 0;
	for (int i = 0; i <= size - oldLen; i++) {
		bool match = true;
		for (int j = 0; j < oldLen; j++) {
			if (Cs[i + j] != old[j]) {
				match = false;
				break;
			}
		}
		if (match) {
			count++;
			i += oldLen - 1;
		}
	}
	int newS = size + count * (newLen - oldLen);
	MyString temp;
	temp.size = newS + 1;
	temp.Cs = new char[newS + 1];
	int sInd = 0, dInd = 0;
	while (sInd < size) {
		bool match = false;
		if (sInd <= size - oldLen) {
			match = true;
			for (int j = 0; j < oldLen; j++) {
				if (Cs[sInd + j] != old[j]) {
					match = false;
					break;
				}
			}
		}

		if (match) {
			for (int k = 0; k < newLen; k++)
				temp.Cs[dInd++] = newStr[k];
			sInd += oldLen;
		}
		else {
			temp.Cs[dInd++] = Cs[sInd++];
		}
	}
	temp.Cs[newS] = '\0';
	return temp;
}

MyString* MyString::Split(char delim, int& count) const
{
	int parts = 1;
	for (int i = 0; i < size; i++)
		if (Cs[i] == delim)
			parts++;
	count = parts;
	MyString* res = new MyString[count];
	int s = 0, ind = 0;
	for (int i = 0; i <= size; i++) {
		if (Cs[i] == delim or Cs[i] == '\0') {
			int len = i - s;
			char* buf = new char[len + 1];
			for (int k = 0; k < len; k++) {
				buf[k] = Cs[s + k];
			}
			buf[len] = '\0';
			res[ind++] = MyString(buf);
			delete[] buf;
			s = i + 1;

		}
	}
	return res;

}

MyString* MyString::Tokenize(const char* delimiters, int& count) const {
	count = 0;
	bool inToken = false;

	for (int i = 0; i < size; i++) {
		bool isDelim = false;
		for (int j = 0; delimiters[j] != '\0'; j++) {
			if (Cs[i] == delimiters[j]) {
				isDelim = true;
				break;
			}
		}

		if (!isDelim and !inToken) {
			count++;
			inToken = true;
		}
		else if (isDelim) {
			inToken = false;
		}
	}

	if (count == 0) return nullptr;
	MyString* res = new MyString[count];

	int ind = 0;
	int s = -1;

	for (int i = 0; i <= size; i++) {
		bool isDelim = (Cs[i] == '\0');
		for (int j = 0; delimiters[j] != '\0' && !isDelim; j++) {
			if (Cs[i] == delimiters[j]) {
				isDelim = true;
			}
		}

		if (!isDelim && s == -1) {
			s = i;
		}
		else if (isDelim and s != -1) {
			int len = i - s;
			char* buf = new char[len + 1];
			for (int k = 0; k < len; k++) {
				buf[k] = Cs[s + k];
			}
			buf[len] = '\0';

			res[ind++] = MyString(buf);
			delete[] buf;
			s = -1;
		}
	}

	return res;
}

MyString MyString::SubstrIter(Iterator start, Iterator end)
{
	int len = start.distanceTo(end);
	if (len <= 0)
		return MyString("");
	char* buf = new char[len + 1];
	Iterator it = start;
	int i = 0;
	while (it.notEquals(end)) {
		buf[i++] = it.get();
		it.next();
	}
	buf[len] = '\0';
	MyString Res(buf);
	delete[]buf;
	return Res;
}
void MyString::InsertAt(Iterator pos, const MyString& str)
{
	int insertInd = begin().distanceTo(pos);
	if (insertInd < 0 or insertInd> size)
		return;
	int newSize = size + str.length();
	char* newCs = new char[newSize + 1];

	for (int i = 0; i < insertInd; i++) {
		newCs[i] = Cs[i];
	}
	for (int i = 0; i < str.length(); i++) {
		newCs[insertInd + i] = str.CharacterAt(i);
	}
	for (int i = insertInd; i < size; i++) {
		newCs[str.length() + i] = Cs[i];
	}
	newCs[newSize] = '\0';
	delete[] Cs;
	Cs = newCs;
	size = newSize;
}

void MyString::EraseRange(Iterator start, Iterator end)
{
	int si = begin().distanceTo(start);
	int ei = begin().distanceTo(end);
	if (si<0 or ei>size or si >= ei)
		return;
	int eraseLen = ei - si;
	int newS = size - eraseLen;
	char* newCs = new char[newS + 1];
	for (int i = 0; i < si; i++) {
		newCs[i] = Cs[i];
	}
	for (int i = ei; i < size; i++) {
		newCs[si + i - ei] = Cs[i];
	}
	newCs[newS] = '\0';
	delete[] Cs;
	Cs = newCs;
	size = newS;
}

MyString::Iterator MyString::Find(char c)
{
	return FindFrom(begin(), c);
}
MyString::Iterator MyString::FindFrom(Iterator start, char c) {
	Iterator it = start;
	while (it.notEquals(end())) {
		if (it.get() == c) {
			return it;
		}
		it.next();
	}
	return end();
}
void MyString::insert(int pos, char ch) {
	if (pos < 0 or pos > size)
		return;
	char* newCs = new char[size + 2];
	for (int i = 0; i < pos; i++)
		newCs[i] = Cs[i];
	newCs[pos] = ch;
	for (int i = pos; i < size; i++)
		newCs[i + 1] = Cs[i];
	newCs[size + 1] = '\0';
	delete[] Cs;
	Cs = newCs;
	size++;
}

const char* MyString::c_str() const {
	return Cs;
}