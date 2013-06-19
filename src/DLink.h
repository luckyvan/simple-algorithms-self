
#ifndef MY_DLINK
#define MY_DLINK
//double-linked list node
namespace MyList{
	struct _DLink_base{
		_DLink_base* next;
		_DLink_base* prev;

	};

template <class _Elem> class _DLink: public _DLink_base{
	private:
		static _DLink<_Elem>* freelist; //Head of free link list
	public:
		_Elem element;

		void* operator new(size_t);
		void operator delete(void*);
};

template <class _Elem> 
_DLink<_Elem>* _DLink<_Elem>::freelist = NULL;

template <class _Elem>
void* _DLink<_Elem>::operator new(size_t){
	if(freelist == NULL) return ::new _DLink<_Elem>();
	_DLink<_Elem>* temp = freelist;
	freelist = (_DLink<_Elem>*)freelist->next;
	return temp;
}

template <class _Elem>
void _DLink<_Elem>::operator delete(void* ptr){
	((_DLink<_Elem>*)ptr)->next = freelist;
	freelist = (_DLink<_Elem>*)ptr;
}
}
#endif
