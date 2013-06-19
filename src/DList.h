#ifndef MY_DLIST
#define MY_DLIST
#include <cstddef>
#include <iterator>

using namespace std;

namespace MyList{
	//Link
	/* *
	 * DList node base without Element Info.
	 * */
	struct _DLink_base{
		_DLink_base* next;
		_DLink_base* prev;
	};
	
	/* *
	 * DList node use free element list to reduce memory allocation
	 * */
	template <class _Elem> 
		class _DLink: public _DLink_base{
			typedef _DLink<_Elem> link_type;
	
			private:
				static link_type* freelist; //Head of free link list
			public:
				_Elem element;
		
				void* operator new(size_t){
					if(freelist == NULL) return ::new link_type();
					link_type* temp = freelist;
					freelist = (link_type*)freelist->next;
					return temp;
				}
	
				void operator delete(void* ptr){
					((link_type*)ptr)->next = freelist;
					freelist = (link_type*)ptr;
				}
		};
		
	
	template <class _Elem> 
		_DLink<_Elem>* _DLink<_Elem>::freelist = NULL;
	
	
	//Iterator
		struct _DList_iterator_base{
			_DLink_base* link;

			_DList_iterator_base(){}
			_DList_iterator_base(_DLink_base*  __x):
				link(__x){}

			void _M_incr() { link = link->next; }
			void _M_decr() { link = link->prev; }

			bool operator==(const _DList_iterator_base& __x) const {
				return link == __x.link;
			}

			bool operator!=(const _DList_iterator_base& __x) const {
				return link != __x.link;
			}
		};

	template <class _Elem, class _Ref, class _Ptr>
		struct _DList_iterator: public _DList_iterator_base{
			//associated types
		    typedef _Elem value_type;
			typedef _Ptr  pointer;
			typedef _Ref  reference;
			typedef size_t	size_type;
			typedef	ptrdiff_t difference_type;
			typedef bidirectional_iterator_tag iterator_category; //iterator model

			//inner used
			typedef _DList_iterator<_Elem, _Elem&, _Elem*> iterator;	
			typedef _DList_iterator<_Elem, const _Elem&, const _Elem*> const_iterator;	
			typedef _DList_iterator<_Elem, _Ref, _Ptr> _Self;
			typedef _DLink<_Elem> link_type;

			_DList_iterator(_DLink<_Elem>* __x):_DList_iterator_base(__x){}
			_DList_iterator(){}
			_DList_iterator(const iterator& __x): _DList_iterator_base(__x.link){}

			reference operator*() const { return ((link_type*)link)->element;}

			_Self& operator++(){
				this->_M_incr();
				return *this;
			}

			_Self operator++(int){
				_Self tmp = *this;
				this->_M_incr();
				return tmp;
			}

			_Self& operator--(){
				this->_M_decr();
				return *this;
			}

			_Self operator--(int){
				_Self tmp = *this;
				this->_M_decr();
				return tmp;
			}
		};

	template <class Elem>
		class DList{
			typedef Elem value_type;
			typedef Elem* pointer;
			typedef Elem& reference;
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
			typedef _DList_iterator<Elem, Elem&, Elem*> iterator;

			typedef _DLink<Elem> link_type;

			protected:
			link_type* get_node(){
				return new link_type();	
			}

			void put_node(link_type* n){
				delete n;
			}

			link_type* create_node(const Elem& elem){
				link_type* n = get_node();
				n->element = elem;
			}

			void destroy_noda(link_type* n){
				put_node(n);
			}

			void empty_initialize(){
				node = new _DLink<Elem>(); //sentinel
				node->next = node;
			   	node->prev = node;	
			}

			void transfer(iterator pos, iterator first, iterator last){
				if(pos != last){
					(last.link)->prev->next = pos.link;
					(first.link)->prev->next = last.link;
					pos.link->prev->next = first.link;

					_DLink_base* tmp = pos.link->prev;
					pos.link->prev = last.link->prev;
					last.link->prev = first.link->prev;
					first.link->prev = tmp;
				}
			}

			private:
			_DLink<Elem> *node; // node ptr to the end sentinel, and the whole list forms a circle
			public:
			DList(){
				empty_initialize();
			}

			template<class ForwardIterator>
			DList(ForwardIterator first, ForwardIterator last){
				empty_initialize();
				while(first != last){
					push_back(*first);
					first++;
				}
			}

			~DList(){
				clear();
			}
			
			iterator begin(){
				return (link_type*)node->next;
			}

			iterator end(){
				return (link_type*)node;
			}

			reference front(){
				return *begin();
			}

			reference back(){
				return *(--end());
			}

			size_t size(){
				size_type s = 0;
				for(iterator cur = begin(); cur != end(); 
						s++, cur++);
				return s;
			}

			bool empty(){
				return begin() == end();
			}

			void insert(iterator pos, const Elem& elem){
				link_type* tmp = create_node(elem);

				tmp->next = pos.link;
				tmp->prev = pos.link->prev;
				pos.link->prev->next = tmp;

				pos.link->prev= tmp;
			}

			void erase(iterator pos){
				link_type* next = (link_type*)(pos.link->next);
				link_type* prev = (link_type*)(pos.link->prev);
				prev->next = next;
				next->prev = prev;
				destroy_node((link_type*)(pos.link));
				return next;
			}

			void push_front(const Elem& e){
				insert(begin(), e);
			}

			void push_back(const Elem& e){
				insert(end(), e);
			}

			void pop_front(){
				erase(begin());
			}

			void reverse(){
				if(empty() || (link_type*)(node->next)->next == node) return;

				iterator first = begin();
				++first; 
				while(first != end()){
					iterator old = first;
					++first;
					transfer(begin(), old, first);
				}
			}

			void clear(){}
		};

}

#endif
