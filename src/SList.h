#ifndef MY_SLIST
#define MY_SLIST
#include "List.h"
#include "Link.h"

namespace MyList{
	template <class Elem>
		class SList{
			Link<Elem> *head;
			public:
			SList(){
				head = new Link<Elem>(); //sentinel
				head->next = end();
			}

			~SList(){
				clear();
			}
			
			Link<Elem>* begin(){
				return head->next;
			}

			Link<Elem>* end(){
				return (Link<Elem>*)NULL;
			}

			Elem front(){
				return begin()->element;
			}

			size_t size(){
				Link<Elem>** linkp = &(head->next);
				size_t s = 0;
				Link<Elem>* cur;
				while((cur = *linkp) != end()){
					s++;
					linkp = &cur->next;
				}
				return s;
			}

			bool empty(){
				return begin() == end();
			}

			void push_front(const Elem& e){
				Link<Elem>* node = new Link<Elem>();
				node->element = e;
				node->next = (head)->next;
				(head->next) = node;
			}

			void pop_front(){
				Link<Elem>* node = begin();
				head->next = node->next;
				delete node;
			}

			void reverse(){
				if(empty() || begin()->next == end()) return;

				Link<Elem>* prev = end();
				Link<Elem>* cur = begin();
				Link<Elem>* next = begin()->next;
				while(cur != end()){
					cur->next = prev;
					prev = cur;
					cur = next;
					if(cur != end())
						next = cur->next;
				}
				head->next = prev;
			}

			void clear(){}
		};

}

#endif
