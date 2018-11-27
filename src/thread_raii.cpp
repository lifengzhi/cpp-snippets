#include <iostream>

#include <thread>
#include <type_traits>

namespace meyers {
// Effective Modern C++ by Scott Meyers (O’Reilly).
// Copyright 2015 Scott Meyers, 978-1-491-90399-5
// Item 37: Make std::threads unjoinable on all paths.
class thread_raii {
 public:
  enum class dtor_action { join, detach };

  // 1 - The constructor accepts only std::thread rvalues, because we want to
  // move the passed-in std::thread into the thread_raii object. (Recall that
  // std::thread objects aren’t copyable.)
  // 2 - The parameter order in the constructor is designed to be intuitive to
  // callers (specifying the std::thread first and the destructor action second
  // makes more sense than vice versa), but the member initialization list is
  // designed to match the order of the data members’ declarations. That order
  // puts the std::thread object last. In this class, the order makes no
  // difference, but in general, it’s possible for the initialization of one
  // data member to depend on another, and because std::thread objects may start
  // running a function immediately after they are initialized, it’s a good
  // habit to declare them last in a class. That guarantees that at the time
  // they are constructed, all the data members that precede them have already
  // been initialized and can therefore be safely accessed by the asynchronously
  // running thread that corresponds to the std::thread data member.
  thread_raii(std::thread&& t, dtor_action a)
      : action(a), thread(std::move(t)) {}

  ~thread_raii() {
    // 3 - Before the thread_raii destructor invokes a member function on the
    // std::thread object t, it checks to make sure that t is joinable. This is
    // necessary, because invoking join or detach on an unjoinable thread yields
    // undefined behavior. It’s possible that a client constructed a
    // std::thread, created a thread_raii object from it, used get to acquire
    // access to t, and then did a move from t or called join or detach on it.
    // Each of those actions would render t unjoinable.
    if (thread.joinable()) {
      if (action == dtor_action::join) {
        thread.join();
      } else {
        thread.detach();
      }
    }
  }

  // Added: Rule of five for better readability
  thread_raii(thread_raii const&) = delete;
  thread_raii& operator=(thread_raii const&) = delete;
  // 4 - Item 17 explains that because thread_raii declares a destructor, there
  // will be no compiler-generated move operations, but there is no reason
  // thread_raii objects shouldn’t be movable. If compilers were to generate
  // these functions, the functions would do the right thing, so explicitly
  // requesting their creation is appropriate.
  thread_raii(thread_raii&&) = default;
  thread_raii& operator=(thread_raii&&) = default;

  // 5 - thread_raii offers a get function to provide access to the underlying
  // std::thread object. This is analogous to the get functions offered by the
  // standard smart pointer classes that give access to their underlying raw
  // pointers. Providing get avoids the need for thread_raii to replicate the
  // full std::thread interface, and it also means that thread_raii objects can
  // be used in contexts where std::thread objects are required.
  std::thread& get() { return thread; }

 private:
  dtor_action action;
  std::thread thread;
};

static_assert(!std::is_copy_constructible_v<thread_raii>);
static_assert(!std::is_copy_assignable_v<thread_raii>);
static_assert(std::is_move_assignable_v<thread_raii>);
static_assert(std::is_move_constructible_v<thread_raii>);

}  // namespace meyers

namespace williams {
// C++ Concurrency in Action by Anthony Williams
// Copyright 2012 Manning Publications Co., 978-1-933-98877-1
// Listing 2.6 scoped_thread and example usage
class scoped_thread {
  std::thread t;

 public:
  explicit scoped_thread(std::thread t_) : t(std::move(t_)) {
    if (!t.joinable()) throw std::logic_error("No thread.");
  }
  ~scoped_thread() { t.join(); }

  // Added: Rule of five for better readability
  scoped_thread(scoped_thread const&) = delete;
  scoped_thread& operator=(scoped_thread const&) = delete;
  // Added: re-enable move semantics (like meyers::thread_raii)
  scoped_thread(scoped_thread&&) = default;
  scoped_thread& operator=(scoped_thread&&) = default;
};

static_assert(!std::is_copy_constructible_v<scoped_thread>);
static_assert(!std::is_copy_assignable_v<scoped_thread>);
static_assert(std::is_move_assignable_v<scoped_thread>);
static_assert(std::is_move_constructible_v<scoped_thread>);

}  // namespace williams

namespace stroustrup {
// The C++ Programming Language, Fourth Edition by Bjarne Stroustrup
// Copyright 2013 by Pearson Education, Inc., 978-0-321-56384-2
// Section 42.2.4 join()
struct guarded_thread : std::thread {
  // inherit the thread class' constructor
  // $20.3.5.1
  using std::thread::thread;
  ~guarded_thread() {
    if (joinable()) {
      join();
    }
  }

  // Added: Rule of five for better readability
  guarded_thread(guarded_thread const&) = delete;
  guarded_thread& operator=(guarded_thread const&) = delete;
  // Added: re-enable move semantics (like meyers::thread_raii)
  guarded_thread(guarded_thread&&) = default;
  guarded_thread& operator=(guarded_thread&&) = default;
};

static_assert(!std::is_copy_constructible_v<guarded_thread>);
static_assert(!std::is_copy_assignable_v<guarded_thread>);
static_assert(std::is_move_assignable_v<guarded_thread>);
static_assert(std::is_move_constructible_v<guarded_thread>);

}  // namespace stroustrup

int main() {
  meyers::thread_raii meyers_thread{
      std::thread{[]() { std::cout << "Hello world (Meyers)!\n"; }},
      meyers::thread_raii::dtor_action::join};

  // auto nh{meyers_thread.get().native_handle()};

  williams::scoped_thread williams_thread{
      std::thread([]() { std::cout << "Hello world (Williams)!\n"; })};

  stroustrup::guarded_thread stroustrup_thread{
      []() { std::cout << "Hello world (Stroustrup)!\n"; }};
}
