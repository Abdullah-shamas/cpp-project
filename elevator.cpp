#include <iostream>
using namespace std;
class floor {
	private:
		floor *head;
		floor *temp;
		floor *current;
	public:
		int floor_number;
		string person;
		floor *next;
		floor *prev;
		floor() {
			head = NULL;
		}
		void add_floor(int f) {
			if (head == NULL) {
				temp = new floor;
				temp->floor_number = f;
				temp->person = "";
				temp->next = NULL;
				temp->prev = NULL;
				head = temp;
			} else {
				current = head;
				while (current->next != NULL) {
					current = current->next;
				}
				temp = new floor;
				temp->floor_number = f;
				temp->person = "";
				temp->next = NULL;
				temp->prev = current;
				current->next = temp;


			}
		}
		void insert_person(int flo, string name) {
			current = head;
			while (current != NULL) {
				if (current->floor_number == flo) {
					current->person = name;
					cout << name << "is on floor " << flo << endl;
					return;
				}
				current = current->next;

			}
			cout << "floor " << flo << "not found." << endl;
		}
		void move_person(int from_floor, int to_floor) {
			current = head;
			floor *from = NULL; 
			floor *to = NULL;   
			while (current != NULL) {
				if (current->floor_number == from_floor) {
					from = current;
				}
				if (current->floor_number == to_floor) {
					to = current;
				}
				current = current->next;
			}


			cout << from->person << " on floor " << from_floor
			     << " is swapped with " << to->person << " on floor " << to_floor << ".\n";
			swap(from->person, to->person);

		}
		void delete_floor(int floor_number) {
			current = head;

			while (current != NULL && current->floor_number != floor_number) {
				current = current->next;
			}
                if(current==head){
                	temp=head;
                	head=head->next;
                	head->prev=NULL;
                	delete temp;
				}
				else if(current->next==NULL){
					temp=current->next;
					temp->prev->next=NULL;
					delete temp;
				}
		    else 
		    temp=current;
		    current->next->prev=current->prev;
		    current->prev->next=current->next;
		    delete temp;
		}


		void display() {
			current = head;
			while (current != NULL) {
				cout << "floor" << current->floor_number << ":" << (current->person.empty() ? "empty" : current->person) << endl;
				current = current->next;
			}
		}

};

int main() {
	floor e;
	e.add_floor(1);
	e.add_floor(2);
	e.add_floor(3);
	e.insert_person(1, "ahmad");
	e.insert_person(2, "hassan");
	e.insert_person(3, "haseeb");
	e.display();
	e.move_person(1, 3);
	e.display();
	e.delete_floor(2);
	e.display();
}