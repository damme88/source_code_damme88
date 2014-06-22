#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace Basic {
  template<typename Type>
  struct DefaultSingletonTraits {
    static Type* New() {
      return new Type();
    }
    static void Delete(Type* x) {
      delete x;
    }
  };


  template<typename Type, typename Traits = DefaultSingletonTraits<Type>>
  class Singleton {
  public:
    static Type* Get() {
      if (NULL != instance_) {
        return instance_;
      }
      instance_ = Traits::New();
      static CleanUp clean_up;
      return instance_;
    }

  private:
    struct CleanUp {
      ~CleanUp() {
        if (NULL != Singleton::instance_) {
          Traits::Delete(Singleton::instance_);
          Singleton::instance_ = NULL;
        }
      }
    }
    friend struct CleanUp;
    static Type* instance_;
  };
}
#endif // SINGLETON_H_