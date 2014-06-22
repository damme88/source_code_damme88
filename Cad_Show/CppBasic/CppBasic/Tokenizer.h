#ifndef TOKENIZER_H_
#define TOKENIZER_H_
#include <string>
namespace basic {
  template<typename charT>
  class Tokenizer {
  public:
    typedef std::basic_string<charT> Strings;
    Tokenizer(const Strings& str, const Strings& delimiters) :
      string_(str),
      offset_(0),
      delimeters_(delimiters) {
      
    }

    ~Tokenizer() {;}
    bool NexToken() {
      size_t i = string_.find_first_not_of(delimeters_, offset_);
      if (Strings::npos == i) {
        offset_ = string_.length();
        return false;
      } else {
        offset_ = i;
      }
      size_t j = string_.find_first_not_of(delimeters_, offset_);
      if (Strings::npos == j) {
        token_ = string_.substr(i);
        offset_ = string_.length();
        return true;
      }
      token_ = string_.substr(i, j-1);
      offset_ = j;
      return true;
    }
    Strings GetToken() {return token_;}
  private:
    size_t offset_;
    const Strings string_;
    Strings token_;
    Strings delimeters_;
  };
}

#endif // TOKENIZER_H_