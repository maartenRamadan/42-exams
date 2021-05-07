#include "ASpell.hpp"

ASpell::ASpell() {
}

ASpell::ASpell(const ASpell& rhs) {
	*this = rhs;
}

ASpell& ASpell::operator=(const ASpell& rhs) {
	(void)rhs;
	return *this;
}

ASpell::ASpell(const std::string& n, const std::string& e): name(n), effects(e) {
}

ASpell::~ASpell() {
}

const std::string& ASpell::getName() const {
	return name;
}

const std::string& ASpell::getEffects() const {
	return effects;
}

void ASpell::launch(const ATarget& target) {
	target.getHitBySpell(*this);
}
