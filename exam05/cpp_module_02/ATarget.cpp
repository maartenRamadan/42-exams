#include "ATarget.hpp"

ATarget::ATarget() {
}

ATarget::ATarget(const ATarget& rhs) {
	*this = rhs;
}

ATarget& ATarget::operator=(const ATarget& rhs) {
	(void)rhs;
	return *this;
}

ATarget::ATarget(const std::string& t): type(t) {
}

ATarget::~ATarget() {
}

const std::string& ATarget::getType() const {
	return type;
}

void ATarget::getHitBySpell(const ASpell& spell) const {
	std::cout << type << " has been " << spell.getEffects() << "!" << std::endl;
}
