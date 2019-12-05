#include "MultiplicativeGroupModN.h"

MultiplicativeGroupModN::MultiplicativeGroupModN(int modulo) {
	if (modulo <= 0) {
		throw std::invalid_argument("The modulo can not be <= 0.");
	}
	ModField n(std::to_string(modulo));
	for (int i = 1; i < modulo; i++) {
		if (gcd(i, modulo) == 1) {
			elements.emplace_back(new LongModInt(std::to_string(i), &n));
		}
	}
	order = new LongModInt(std::to_string(elements.size()), &n);
}

LongModInt MultiplicativeGroupModN::getOrder() {
	return *order;
}

std::ostream& operator<<(std::ostream& stream, const MultiplicativeGroupModN& group)
{
	for (LongModInt* element : group.elements) {
		cout << *element;
	}
	return stream;
}
