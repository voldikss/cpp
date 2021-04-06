#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template <typename T>
class Less_than {
    const T val;

  public:
    Less_than(const T &v) : val(v) {}
    bool operator()(const T &x) const {
        return x < val;
    }
};

class IncreaseingNumberGenerator {
  public:
    int operator()() noexcept {
        return number++;
    }

  private:
    int number{0};
};

template <typename T>
void print(const std::vector<T> &vec) {
    for (const T &x : vec)
        cout << x << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    Less_than<int> lti{42};
    cout << lti(41) << endl;

    std::vector<int> numbers(10);
    print(numbers);
    std::generate(begin(numbers), end(numbers), IncreaseingNumberGenerator());
    print(numbers);
}
