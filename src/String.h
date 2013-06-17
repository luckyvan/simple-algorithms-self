#include <string.h>
#include <algorithm>
#include <iostream>

class String{
	size_t len_;
	char * buffer_;
	public:
		String(size_t len = 0):len_(len),
			buffer_((len==0)?NULL: new char[len]){}

		String(const char* str){
			len_ = strlen(str);
			buffer_ = new char[len_+1];
			strcpy(buffer_, str);	
		}

		~String(){
			if(buffer_ != 0)
				delete [] buffer_;
		}

		String(const String& s):len_(s.length()), buffer_(new char[s.length()+1]){
			strcpy(buffer_, s.buffer_);
		}

		String& operator=(const String& s){
			if(this != &s)
				String(s).swap(*this);
			return *this;
		}

		size_t length() const {return len_;}

		friend std::ostream& operator<<(std::ostream&, const String&);
	private:
		void swap (String& s) throw(){
			std::swap(this->buffer_, s.buffer_);
		}
};

std::ostream& operator<<(std::ostream& o, const String& s){
	return 	o<<s.buffer_;
}
