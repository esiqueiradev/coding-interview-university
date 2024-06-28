#include <iostream>
#include <stdexcept>

static char const *INDEX_OUT_OF_RANGE_ERROR = "Index out of range";

template <typename T>
class CustomVector
{
private:
  T *array;
  size_t _size;
  size_t _capacity;

  void resize(size_t new_capacity)
  {
    T *new_array = new T[new_capacity];

    for (size_t i = 0; i < _size; i++)
    {
      new_array[i] = array[i];
    }

    delete[] array;

    array = new_array;
    _capacity = new_capacity;
  }

public:
  CustomVector() : array(nullptr), _size(0), _capacity(0) {}

  ~CustomVector()
  {
    delete[] array;
  }

  CustomVector(const CustomVector &other) : _size(other._size), _capacity(other._capacity)
  {
    array = new T[_capacity];

    for (size_t i = 0; i < _size; i++)
    {
      array[i] = other.array[i];
    }
  }

  size_t size() const
  {
    return _size;
  }

  size_t capacity() const
  {
    return _capacity;
  }

  bool empty() const
  {
    return _size == 0;
  }

  T &operator[](size_t index)
  {
    return array[index];
  }

  const T &operator[](size_t index) const
  {
    return array[index];
  }

  T &at(size_t index)
  {
    if (index >= _size)
    {
      throw std::out_of_range(INDEX_OUT_OF_RANGE_ERROR);
    }

    return array[index];
  }

  const T &at(size_t index) const
  {
    if (index >= _size)
    {
      throw std::out_of_range(INDEX_OUT_OF_RANGE_ERROR);
    }

    return array[index];
  }

  void push(const T &value)
  {
    if (_size == _capacity)
    {
      resize(_capacity == 0 ? 1 : _capacity * 2);
    }

    array[_size++] = value;
  }

  void pop()
  {
    if (_size > 0)
    {
      --_size;
    }
  }

  void print()
  {
    for (size_t i = 0; i < _size; ++i)
    {
      std::cout << array[i] << " ";
    }

    std::cout << std::endl;
  }

  void insert(size_t index, const T &value)
  {
    if (index > _size)
    {
      throw std::out_of_range(INDEX_OUT_OF_RANGE_ERROR);
    }

    if (_size == _capacity)
    {
      resize(_capacity == 0 ? 1 : _capacity * 2);
    }

    for (size_t i = _size; i > index; --i)
    {
      array[i] = array[i - 1];
    }

    array[index] = value;
    ++_size;
  }

  void prepend(const T &value)
  {
    if (_size == _capacity)
    {
      resize(_capacity == 0 ? 1 : _capacity * 2);
    }

    for (size_t i = _size; i > 0; --i)
    {
      array[i] = array[i - 1];
    }

    array[0] = value;
    ++_size;
  }

  void deleteAt(size_t index)
  {
    if (index >= _size)
    {
      throw std::out_of_range(INDEX_OUT_OF_RANGE_ERROR);
    }

    for (size_t i = index; i < _size - 1; ++i)
    {
      array[i] = array[i + 1];
    }

    --_size;
  }

  long find(const T value)
  {
    for (size_t i = 0; i < _size; ++i)
    {
      if (value == array[i])
      {
        return i;
      }
    }

    return -1;
  }
};

int main()
{
  CustomVector<int> vec;

  vec.push(1);
  vec.push(12);
  vec.push(5);
  vec.push(54);

  vec.print();

  vec.pop();

  vec.print();

  vec.deleteAt(0);

  vec.print();

  vec.insert(0, 50);

  vec.print();

  std::cout << vec.at(1) << std::endl;

  vec.prepend(17);

  vec.print();

  std::cout << vec.find(17) << std::endl; // 0
  std::cout << vec.find(22) << std::endl; // -1

  return 0;
}