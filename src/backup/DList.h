#ifndef MY_DLIST
#define MY_DLIST
#include "DLink.h"
namespace MyList{
	template <class Elem>
		class DList{
			typedef DLink<Elem>* link_type;
			protected:
			link_type get_node(){
				return new DLink<Elem>();	
			}

			void put_node(link_type n){
				delete n;
			}

			link_type create_node(const Elem& elem){
				link_type n = get_node();
				n->element = elem;
			}

			void destroy_node(link_type n){
				put_node(n);
			}

			void empty_initialize(){
				node = new DLink<Elem>(); //sentinel
				node->next = node;
			   	node->prev = node;	
			}

			void transfer(link_type pos, link_type first, link_type last){
				last->prev->next = pos;
				first->prev->next = last;
				pos->prev->next = first;
				link_type tmp = pos->prev;
				pos->prev = last->prev;
				last->prev = first->prev;
				first->prev = tmp;
			}

			private:
			DLink<Elem> *node; // node ptr to the end sentinel, and the whole list forms a circle
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
			
			DLink<Elem>* begin(){
				return node->next;
			}

			DLink<Elem>* end(){
				return node;
			}

			Elem front(){
				return begin()->element;
			}

			Elem back(){
				return end()->prev->element;
			}

			size_t size(){
				size_t s = 0;
				for(DLink<Elem>* cur = begin(); cur != end(); 
						s++, cur=cur->next);
				return s;
			}

			bool empty(){
				return begin() == end();
			}

			void insert(DLink<Elem>* pos, const Elem& elem){
				link_type tmp = create_node(elem);

				tmp->next = pos;
				tmp->prev = pos->prev;
				pos->prev->next = tmp;

				pos->prev= tmp;
			}

			void erase(link_type pos){
				link_type next = pos->next;
				link_type prev = pos->prev;
				prev->next = next;
				next->prev = prev;
				destroy_node(pos);
				return next;
			}

			void push_front(const Elem& e){
				insert(begin(), e);
			}

			void push_back(const Elem& e){
				insert(end(), e);
			}

			void pop_front(){
				DLink<Elem>* node = begin();
				node->next = node->next;
				delete node;
			}

			void reverse(){
				if(empty() || begin()->next == end()) return;

				link_type first = begin();
				first = first->next;
				while(first != end()){
					link_type old = first;
					first = first->next;
					transfer(begin(), old, first);
				}
			}

			void clear(){}
		};

}

#endif
