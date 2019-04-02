#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <string>

using namespace boost::python;

template <typename Container>
list stl2py(const Container& vec) 
{
  typedef typename Container::value_type T;
  list lst;
  std::for_each(vec.begin(), vec.end(), [&](const T& t) { lst.append(t); });
  return lst;
}

template <typename Container>
void py2stl(const list& lst, Container& vec) 
{
  typedef typename Container::value_type T;
  stl_input_iterator<T> beg(lst), end;
  std::for_each(beg, end, [&](const T& t) { vec.push_back(t); });
}