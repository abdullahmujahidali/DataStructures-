#include<iostream>
#include<string>
using namespace std;
// .h file
template <class X>
class Stack
{
 X *stackData;
 int currentIndex;
 int size;
public:
 Stack(int size = 10);
 void push(X);
 X pop();
 X top();
 int getSize();
 bool isEmpty();
 bool isFull();
 void display();
};
// (1) .cpp file
template <class X>
Stack<X>::Stack(int size)
{
 stackData = new X[size];
 this->size = size;
 currentIndex = -1;
}
template <class X>
void Stack<X>::push(X data)
{
 if (!isFull())
 {
  stackData[++currentIndex] = data;
 }
}
template <class X>
X Stack<X>::pop()
{
 if (!isEmpty())
 {
  return stackData[currentIndex--];
 }
}
template <class X>
X Stack<X>::top()
{
 if (!isEmpty())
  return stackData[currentIndex];
}
template <class X>
int Stack<X>::getSize()
{
 return size;
}
template <class X>
bool Stack<X>::isEmpty()
{
 return currentIndex == -1;
}
template <class X>
bool Stack<X>::isFull()
{
 return currentIndex == size - 1;
}
template <class X>
void Stack<X>::display() {
 if (currentIndex>-1)
 {
  cout << "Data : \n\t";
  for (int i = 0; i <= currentIndex; i++)
   cout << stackData[i] << " ";
  cout << "\n";
 }
 else
 {
  cout << "Stack is Empty\n";
 }
}
// (2) .cpp file
//--------------------------------(Functions)--------------------------------------
bool IsOperand(char character)
{
 if (character >= '0' && character <= '9') {
  return true;
 }
 if (character >= 'a' && character <= 'z') {
  return true;
 }
 if (character >= 'A' && character <= 'Z') {
  return true;
    }
 return false;
}
bool IsOperator(char character)
{
 if (character == '+' || character == '-' || character == '*' || character == '/' || character == '%')
 {
  return true;
 }
 return false;
}
int GetoperatorPresidency(char op)
{
 int presidency = 0;
 switch (op)
 {
 case '+':
 case '-':
  presidency = 1;
  break;
 case '*':
 case '/':
 case '%':
  presidency = 2;
  break;
 }
 return presidency;
}
int HasHigherPrecedence(char op1, char op2)
{
 int op1Weight = GetoperatorPresidency(op1);
 int op2Weight = GetoperatorPresidency(op2);
 if (op1Weight == op2Weight)
  return true;
 return op1Weight > op2Weight ? true : false;
}
string Intopostfix(string expression, Stack<char> stack) {
 string postfix = "";
 for (int i = 0; i< expression.length()-1; i++) {  // $ is the end so we are checking before $ sign.
 
  if (IsOperator(expression[i]))
  {
   while (!stack.isEmpty() && stack.top() != '(' && HasHigherPrecedence(stack.top(), expression[i]))
   {
    postfix += stack.top();
    stack.pop();
   }
   stack.push(expression[i]);
  }
  else if (IsOperand(expression[i]))
  {
   postfix += expression[i];
  }
  else if (expression[i] == '(')
  {
   stack.push(expression[i]);
  }
  else if (expression[i] == ')')
  {
   while (!stack.isEmpty() && stack.top() != '(') {
    postfix += stack.top();
    stack.pop();
   }
   stack.pop();
  }
 }
 while (!stack.isEmpty()) {
  postfix += stack.top();
  stack.pop();
 }
 return postfix;
}

//-----------------------------------------------------------------------
void ConvertiontopostFix() {
 string expression;
 cout << "Enter Infix Expression : ";
 getline(cin, expression);
 Stack<char> stack(expression.length());
 cout << "Postfix Expression is : " << (Intopostfix(expression, stack)) << endl;
 cout << endl;
}
//---------------------Main----------------------------------------------------
int main() {
 ConvertiontopostFix();
 return 0;
}
