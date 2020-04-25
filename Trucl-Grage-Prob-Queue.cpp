#include <iostream>
using namespace std;
class node{
private:
	int truck_ID;
	node *next;
public:
	node(){
		truck_ID = 0;
		next = NULL;

	}
	void settruck_ID(int d){
		this->truck_ID = d;
	}

	void setnext(node *n){
		this->next = n;
	}
	int gettruck_ID(){
		return truck_ID;
	}

	node *getnext(){
		return next;
	}
};
class road {
public:
	node *front;
	node *rear;
	road() {
		front = NULL;
		rear = NULL;
	}
	void On_Road(int x) {
		node *temp = new node;
		temp->settruck_ID(x);
		temp->setnext(NULL);
		if (front == NULL && rear == NULL) {
			front = temp;
			rear = temp;
			return;
		}
		rear->setnext(temp);
		rear = temp;
	}
	void Exit_Garage(int val) {
		node *temp = new node;
		if (front == NULL) {
			return;
		}
		if (front == rear) {
			front = NULL;
			rear = NULL;
		}
		else {
			front = front->getnext();
		}
		free(temp);
	}
	void showRoad() {
		node *temp = new node;
		temp = front;
		if ((front == NULL) && (rear == NULL)) {
			cout << "Road is empty" << endl;
			return;
		}
		cout << "Trucks on road are: ";
		while (temp != NULL) {
			cout << temp->gettruck_ID() << " ";
			temp = temp->getnext();
		}
		cout << endl;
	}
};

class garage{
private:
	node *head;
	node *top;
public:
	road *r;
	garage(){
		head = NULL;
		top = NULL;
		r = NULL;
	}

	bool isEmpty(){
		if (top == NULL){
			return true;
		}
	}
	void enter_Garage(int val){
			node *temp = new node;
			temp->settruck_ID(val);
			temp->setnext(top);
			top = (temp);
		}
	void exit_Garage(){
		if (top != NULL){
		
			top = top->getnext();
		}
	}
	void exit_Garage_Val(int val){
		if (top != NULL){
			if (top->gettruck_ID() == val)
			{
		
			}top = top->getnext();
		}
		else{
			cout << val<<"is not at exit" << endl;
		}
	}
	void show_Garage(){
		node *temp = new node;
		temp = top;
		if (top != NULL){
			cout << "Trucks in Garage are: ";
			while (temp != NULL) {
				cout << temp->gettruck_ID() << " ";
				temp = temp->getnext();
			}
			cout << endl;
		}
		else{
			cout << "Garage is empty" << endl;
		}
	}
};

void menu(){
	cout << "1. Add truck on road" << endl;
	cout << "2. Add truck from garage to road" << endl;
	cout << "3. Exit from garage" << endl;
	cout << "4. Show truck on road" << endl;
	cout << "5. Show truck on garage" << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	garage g;
	road r;
	int choice;
	r.On_Road(2);
	r.On_Road(5);
	r.On_Road(10);
	r.On_Road(9);
	r.On_Road(22);
	r.showRoad();
	g.show_Garage();
	g.enter_Garage(2);
	r.Exit_Garage(2);
	r.showRoad();
	g.show_Garage();
	g.enter_Garage(10);
	g.enter_Garage(25);
	g.exit_Garage_Val(10);
	g.exit_Garage();
	g.exit_Garage_Val(2);
	g.exit_Garage();
	g.show_Garage();
	return 0;
}

