// https://www.heise.de/developer/artikel/C-Core-Guidelines-Smart-Pointer-als-Funktionsparameter-3927673.html
// https://stackoverflow.com/a/29089295/496459

#include <iostream>
#include <memory>
#include <vector>

struct s_data {
  int m_id;
};

class c_data {
  int m_id;

 public:
  explicit c_data(int id) : m_id(id) {}
  ~c_data() { std::cout << "delete id: " << m_id << '\n'; }
  auto get_id() const { return m_id; }
  void set_id(int id) { m_id = id; }
};

// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-uniqueptrparam
template <typename T>
void sink_func(std::unique_ptr<T> ptr, std::vector<std::unique_ptr<T>>& vec) {
  vec.push_back(std::move(ptr));
}

int main() {
  // push_back + move
  {
    std::vector<std::unique_ptr<s_data>> vec_s_data;

    for (int i = 0; i < 10; ++i) {
      auto p_data = std::make_unique<s_data>();
      p_data->m_id = i;
      vec_s_data.push_back(std::move(p_data));
    }

    // https://stackoverflow.com/a/20292725/496459
    for (const auto& elem : vec_s_data) {
      std::cout << "id: " << elem->m_id << '\n';
    }

    for (auto& elem : vec_s_data) {
      elem->m_id++;
    }

    for (const auto& elem : vec_s_data) {
      std::cout << "id: " << elem->m_id << '\n';
    }
  }

  std::cout << "--------\n";
  // emplace_back
  {
    std::vector<std::unique_ptr<c_data>> vec_c_data;
    for (int i = 0; i < 10; ++i) {
      vec_c_data.emplace_back(std::make_unique<c_data>(i));
    }

    for (const auto& elem : vec_c_data) {
      std::cout << "id: " << elem->get_id() << '\n';
    }

    for (const auto& elem : vec_c_data) {
      elem->set_id(elem->get_id() + 1);
    }

    for (const auto& elem : vec_c_data) {
      std::cout << "id: " << elem->get_id() << '\n';
    }
  }

  std::cout << "--------\n";
  // Sink function
  {
    std::vector<std::unique_ptr<s_data>> vec_s_data;

    for (int i = 0; i < 10; ++i) {
      auto p_data = std::make_unique<s_data>();
      p_data->m_id = i;
      sink_func(std::move(p_data), vec_s_data);
    }

    for (const auto& elem : vec_s_data) {
      std::cout << "id: " << elem->m_id << '\n';
    }

    for (auto& elem : vec_s_data) {
      elem->m_id++;
    }

    for (const auto& elem : vec_s_data) {
      std::cout << "id: " << elem->m_id << '\n';
    }
  }
}