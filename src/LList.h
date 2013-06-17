#ifndef MY_LLIST
#define MY_LLIST
#include "List.h"
#include "Link.h"
namespace MyList{
template <class Elem> 
class LList: public List<Elem> {
	private:
		Link<Elem>* head;	
		Link<Elem>* tail;
		Link<Elem>* fence;	//Last element on left side
		int leftcnt;
		int rightcnt;

		void init(){
			fence = tail = head = new Link<Elem>();
			leftcnt = rightcnt = 0;
		}

		void removeall(){
			while(head!= NULL){
				fence = head;
				head = head->next;
				delete fence;
			}
		}

	public:
		LList() { init();}
		~LList() { removeall(); }

		void clear() { removeall(); init(); }
		bool insert(const Elem&);
		bool append(const Elem&);
		bool remove(Elem&);
		void setStart(){
			fence = head; rightcnt += leftcnt; leftcnt = 0; 
		}
		void setEnd(){
			fence = tail; leftcnt += rightcnt; rightcnt = 0; 
		}

		void prev();
		void next(){
			if(fence != tail){
				fence = fence -> next; leftcnt++; rightcnt--;
			}		
		}

		int leftLength() const { return leftcnt; }
		int rightLength() const { return rightcnt; }
		bool setPos(int pos);
		bool getValue(Elem& it) const{
			if(rightLength() == 0) return false;
			it = fence->next->element;
			return true;
		}

		void print() const;
};

template <class Elem>
bool LList<Elem>::insert(const Elem& item){
	fence->next = new Link<Elem>(item, fence->next);
	if(tail == fence) tail = fence->next;
	rightcnt++;
	return true;
}

template <class Elem>
bool LList<Elem>::append(const Elem& item){
	tail->next = new Link<Elem>(item, tail->next);
	tail = tail->next;
	rightcnt++;
	return true;
}

//Remove and return first elem in right partition
template <class Elem>
bool LList<Elem>::remove(Elem& item){
	if(fence->next == NULL) return false;
	item = fence->next->element;
	Link<Elem>* ltemp = fence->next;
	fence->next = ltemp->next;
	if(tail == ltemp) tail = fence;
	delete ltemp;
	rightcnt--;

	return true;
}

template <class Elem> void LList<Elem>::prev(){
	Link<Elem>* temp = head;
	if(fence == head) return;
	while(temp->next != fence) temp = temp->next;
	fence = temp;
	leftcnt--, rightcnt++;
}

template <class Elem> bool LList<Elem>::setPos(int pos){
	if(pos < 0 || pos > (rightcnt + leftcnt)) return false;
	fence = head;
	for(int i = 0; i < pos; i++) fence = fence->next;
	return true;
}
		
template <class Elem> void LList<Elem>::print() const{
	Link<Elem>* temp = head;
	while(temp != fence){
		std::cout << temp->next->element << " ";
		temp = temp->next;
	}

	std::cout << "| ";
	while(temp->next != NULL ){
		std::cout << temp->next->element << " ";
		temp = temp->next;
	}
	std::cout << std::endl;

}

}
#endif
