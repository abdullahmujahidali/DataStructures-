#include "stdafx.h"
#include<iostream>
#include<string>
#include <sstream>
#include <ctime>
using namespace std;
#define SIZE 10
//------------------------------------------------------------------------------//
// Class for stack
template <class X>
class stack
{
	X *arr;
	int top;
	int capacity;

public:

	stack(int size = SIZE);

	void push(X);
	X pop();
	X peek();

	int size();
	bool isEmpty();
	bool isFull();
};

template <class X>
stack<X>::stack(int size)
{
	arr = new X[size];
	capacity = size;
	top = -1;
}

template <class X>
void stack<X>::push(X x)
{
	if (!isFull())
	{
		arr[++top] = x;
	}

}

template <class X>
X stack<X>::pop()
{
	if (!isEmpty())
	{
		return arr[top--];
	}
}
template <class X>
X stack<X>::peek()
{
	if (!isEmpty())
		return arr[top];
}

template <class X>
int stack<X>::size()
{
	return top + 1;
}
template <class X>
bool stack<X>::isEmpty()
{
	return top == -1;
}

template <class X>
bool stack<X>::isFull()
{
	return top == capacity - 1;
}
//---------------------------------------------------------------------------------//
int StringToInt(char data){

	return (int)(data - '0');
}
char intToString(int digit){
	return (char)(digit + '0');
}
string add(string first, string second){
	char *useAsFirst, *useAsSecond; string small, greater, Answer;
	int size;
	size = first.length() > second.length() ? first.length() : second.length();
	greater = first.length() > second.length() ? first : second;
	small = first.length() > second.length() ? second : first;
	useAsSecond = new char[size];
	useAsFirst = new char[size];
	for (int i = 0; i < size; i++){
		useAsFirst[i] = greater[i];
		useAsSecond[i] = '0';
	}
	int j = 0;
	for (int i = small.length() - 1; i >= 0; i--){
		useAsSecond[size - 1 - j++] = small[i];
	}

	stack <int> firstNumber(size), secondNumber(size), Sum(size + 1);
	for (int i = 0; i < size; i++)
	{
		firstNumber.push(StringToInt(useAsFirst[i]));
		secondNumber.push(StringToInt(useAsSecond[i]));
	}
	char *a = new char[size + 1];
	int carry = 0;
	int partailSum = 0;
	for (int i = 0; i < size; i++)
	{
		partailSum = ((firstNumber.peek() + secondNumber.peek()) + carry);
		Sum.push((partailSum % 10));
		firstNumber.pop(); secondNumber.pop();
		carry = partailSum / 10;
	}
	Sum.push(carry);
	Answer.resize(greater.length() + 1);
	for (int i = 0; i < size + 1; i++)
	{
		Answer[i] = intToString(Sum.pop());
	}
	return Answer;
}
int main(){
	string first, second;
	cout << "Enterthe First Digit   : ";
	getline(cin, first);
	cout << "Enter the Second Digit : ";
	getline(cin, second);
	cout << "Answer = " << add(first, second)<<endl;
	return 0;
}
