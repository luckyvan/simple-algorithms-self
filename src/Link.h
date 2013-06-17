#ifndef MY_LINK
#define MY_LINK
//singly-linked list node
namespace MyList{
template <class Elem> class Link{
	private:
		static Link<Elem>* freelist; //Head of free link list
	public:
		Elem element;
		Link* next;
		Link(const Elem& elemval, Link* nextval = NULL){
			element = elemval; next = nextval;
		}

		Link(Link* nextval = NULL) { next = nextval; }

		void* operator new(size_t);
		void operator delete(void*);
};

template <class Elem> 
Link<Elem>* Link<Elem>::freelist = NULL;

template <class Elem>
void* Link<Elem>::operator new(size_t){
	if(freelist == NULL) return ::new Link<Elem>();
	Link<Elem>* temp = freelist;
	freelist = freelist->next;
	return temp;
}

template <class Elem>
void Link<Elem>::operator delete(void* ptr){
	((Link<Elem>*)ptr)->next = freelist;
	freelist = (Link<Elem>*)ptr;
}
}
#endif
