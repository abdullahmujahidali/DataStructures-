#include <iostream>
#include <iostream>
using namespace std;
class node{
public:
    int data;
    node *next;
    node(){
    next=NULL;
    }
    node (int val){
    this->data=val;
    }
};
class list{
private:
    node *head;
    node *tail;
public:
    int count;
    list(){
    head=NULL;
    tail=NULL;
    count=0;
    }
    void createnode(int val){
    node *temp=new node;
    temp->data=val;
    if(head==NULL){
        head=temp;
        tail=temp;
        temp=NULL;
    count++;
    }
    }
    void insertAtTail(int val){
		node *temp = new node;
		if(head!=NULL){
		temp->data=val;
		temp->next = NULL;
			tail->next = temp;
			tail = temp;
			cout<<"node inserted"<<endl;
	count++;
	}
    }
    bool update(int value, int up){
		node *temp = new node;
		temp = head;
		if (head == NULL){
			return false;
		}
		else {
			while (temp != NULL){
				if (temp->data == value){
					temp->data=up;
					return true;
				}
				temp = temp->next;
			}
		}
	}
	int Findsum(){
	int sum = 0;
	node *temp = new node;
	temp = head;
	while (temp != NULL){
		sum=temp->data+sum;
		temp=temp->next;
	}

return sum;
}
void deleteVal (int val){

    node *temp=new node;
    node *pre= new node;
    temp=head;
   if(head->data==val){
    node *temp=head;
    head= head->next;
    temp->next=NULL;
    delete temp;
   }
    else{while(temp!=NULL){
        if(temp->data==val){
        pre->next=temp->next;
        temp->next=NULL;
        delete temp;
        }
        pre=temp;
        temp=temp->next;
    }

}
}
void insertPosition(int val, int pos){
	node *pre = new node;
	node *cur = new node;
	node *temp = new node;
	cur = head;

  if(count>pos){
	for (int i = pos; i > 0; i--){
		pre = cur;
		cur = cur->next;
	}
	temp->data = val;
	pre->next = temp;
	temp->next = cur;
}
/*else{
    cout<<"List is out of bound"<<endl;
}*/
}
void display()
{
    node *temp = head;
    if (temp == NULL){
    cout << "List is empty" << endl;
    }
    else{
        while (temp != NULL)
        {
         cout << temp->data << endl;
         temp = temp->next;
			}
		}
	}
};

int main()
{
   list l;
   l.createnode(454);
   l.insertAtTail(45);
   l.insertAtTail(78);
   l.insertAtTail(777);
   l.update(454,77);
   l.display();
    cout<<"Sum is: "<<   l.Findsum()<<endl;
   l.deleteVal(77);
   l.display();
   l.insertPosition(12,2);
   cout<<endl<<"value inserted"<<endl;
   l.display();
    return 0;
}
