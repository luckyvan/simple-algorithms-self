#ifndef ORBIT
#define ORBIT
namespace EOP{
	template<typename T>
		T* collosion_point(T* start, T* end){
			//precondition, transformation T.next and end sentinel should be defined
			T* slow = start;
//			T* fast = slow->next();
//			if(slow != end) return ptr;

/*			while(fast != slow){
				slow = slow->next();
				if(fast != end) return fast;
				fast = fast->next();
				if(fast != end) return fast;
				fast = fast->next();
			}*/

			return 0;
		}

	template<typename T>
		bool terminating(T* start, T* end){
			return end == collosion_point(start, end);
		}

}//end of EOP
#endif
