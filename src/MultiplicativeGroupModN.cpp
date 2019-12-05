#include "MultiplicativeGroupModN.h"
#include "Algorithms.h"
#include "LongInt.h"
#include <algorithm>


MultiplicativeGroupModN::MultiplicativeGroupModN(ModField* f)
{
	for (LongInt i(1); i < f->mod; i = i+1) {
		if (gcd(i, f->mod) == 1) {
			elements.emplace_back(LongModInt(i, f));
		}
	}
	order = LongModInt(LongInt(elements.size()), f);
}

bool MultiplicativeGroupModN::isGroupElement(const LongModInt& element) {
	if(element.getField()->mod != order.getField()->mod)
		return false;

	//binary search
	auto found = std::lower_bound(elements.begin(), elements.end(), element);
	if(found != elements.end() || *found != element)
		return false;
	return true;
}

LongModInt MultiplicativeGroupModN::getOrder() {
	return order;
}

std::ostream& operator<<(std::ostream& stream, const MultiplicativeGroupModN& group)
{
	std::cout << "{ ";
	bool first = true;
	for (LongModInt element : group.elements) {
		if(!first)
			std::cout << ", ";
		std::cout << element;
		first = false;
	}
	std::cout << " }";
	return stream;
}
