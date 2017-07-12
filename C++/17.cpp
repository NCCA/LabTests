#include <algorithm>
#include <array>
#include <numeric>
#include <iostream>
int main()
{
  std::array<int,10> a;
  std::generate(std::begin(a), std::end(a),
	[i=0]() mutable { return ++i; } );
  for (auto v : a)
	std::cout<<v<<' ';
  std::cout<<'\n';


}
