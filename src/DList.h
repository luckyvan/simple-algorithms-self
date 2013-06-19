#ifndef MY_DLIST
#define MY_DLIST
#include "DLink.h"
#include <cstddef>
#include <iterator>

using namespace std;

namespace MyList{
		struct _DList_iterator_base{
			_DLink_base* _M_link;

			_DList_iterator_base(){}
			_DList_iterator_base(_DLink_base*  __x):
				_M_link(__x){}

			void _M_incr() { _M_link = _M_link->next; }
			void _M_decr() { _M_link = _M_link->prev; }

			bool operator==(const _DList_iterator_base& __x) const {
				return _M_link == __x._M_link;
			}

			bool operator!=(const _DList_iterator_base& __x) const {
				return _M_link != __x._M_link;
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
			typedef bidirectional_iterator_tag iterator_category;

			//inner used
			typedef _DList_iterator<_Elem, _Elem&, _Elem*> iterator;	
			typedef _DList_iterator<_Elem, const _Elem&, const _Elem*> const_iterator;	
			typedef _DList_iterator<_Elem, _Ref, _Ptr> _Self;
			typedef _DLink<_Elem> _Link;

			_DList_iterator(_DLink<_Elem>* __x):_DList_iterator_base(__x){}
			_DList_iterator(){}
			_DList_iterator(const iterator& __x): _DList_iterator_base(__x._M_link){}

			reference operator*() const { return ((_Link*)_M_link)->element;}

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

			typedef _DLink<Elem>* _Link;
			protected:
			_Link get_node(){
				return new _DLink<Elem>();	
			}

			void put_node(_Link n){
				delete n;
			}

			_Link create_node(const Elem& elem){
				_Link n = get_node();
				n->element = elem;
			}

			void destroy_noda(_Link n){
				put_node(n);
			}

			void empty_initialize(){
				node = new _DLink<Elem>(); //sentinel
				node->next = node;
			   	node->prev = node;	
			}

			void transfer(iterator pos, iterator first, iterator last){
				if(pos != last){
					(last._M_link)->prev->next = pos._M_link;
					(first._M_link)->prev->next = last._M_link;
					pos._M_link->prev->next = first._M_link;

					_DLink_base* tmp = pos._M_link->prev;
					pos._M_link->prev = last._M_link->prev;
					last._M_link->prev = first._M_link->prev;
					first._M_link->prev = tmp;
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
				return (_Link)node->next;
			}

			iterator end(){
				return (_Link)node;
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
				_Link tmp = create_node(elem);

				tmp->next = pos._M_link;
				tmp->prev = pos._M_link->prev;
				pos._M_link->prev->next = tmp;

				pos._M_link->prev= tmp;
			}

			void erase(iterator pos){
				_Link next = _Link(pos._M_link->next);
				_Link prev = _Link(pos._M_link->prev);
				prev->next = next;
				next->prev = prev;
				destroy_node(_Link(pos._M_link));
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
				if(empty() || _Link(node->next)->next == node) return;

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
