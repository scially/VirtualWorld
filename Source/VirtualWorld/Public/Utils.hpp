#include "CoreMinimal.h"

template<typename Iter>
auto StdContainer2TArray(Iter begin, Iter end)
{
	using value_type = std::iterator_traits<Iter>::value_type;
	TArray<value_type> Array;
	
	while(begin < end)
	{
		Array.Add(*begin);
		begin++;
	}
		
	return Array;
}