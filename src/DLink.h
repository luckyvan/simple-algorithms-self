
#ifndef MY_DLINK
#define MY_DLINK
//double-linked list node
namespace MyList{
template <class Elem> class DLink{
	private:
		static DLink<Elem>* freelist; //Head of free link list
	public:
		Elem element;
		DLink* next;
		DLink* prev;
		void* operator new(size_t);
		void operator delete(void*);
};

template <class Elem> 
DLink<Elem>* DLink<Elem>::freelist = NULL;

template <class Elem>
void* DLink<Elem>::operator new(size_t){
	if(freelist == NULL) return ::new DLink<Elem>();
	DLink<Elem>* temp = freelist;
	freelist = freelist->next;
	return temp;
}

template <class Elem>
void DLink<Elem>::operator delete(void* ptr){
	((DLink<Elem>*)ptr)->next = freelist;
	freelist = (DLink<Elem>*)ptr;
}
}
#endif
