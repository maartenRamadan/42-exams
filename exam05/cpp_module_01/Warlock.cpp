#include "Warlock.hpp"

Warlock::Warlock() {
}

Warlock::Warlock(const Warlock& rhs) {
	*this = rhs;
}

Warlock& Warlock::operator=(const Warlock& rhs) {
	(void)rhs;
	return *this;
}

Warlock::Warlock(const std::string& name, const std::string& title): _name(name), _title(title) {
	std::cout << _name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock() {
	for (std::map<std::string, ASpell*>::iterator it = _spells.begin(); it != _spells.end(); ++it)
		delete it->second;
	
	std::cout << _name << ": My job here is done!" << std::endl;
}

const std::string& Warlock::getName() const {
	return _name;
}

const std::string& Warlock::getTitle() const {
	return _title;
}

void Warlock::setTitle(const std::string& title) {
	_title = title;
}

void Warlock::introduce() const {
	std::cout << _name << ": I am " << _name << ", " << _title << "!" << std::endl;
}

void Warlock::learnSpell(ASpell* spell) {
	_spells[spell->getName()] = spell;
}

void Warlock::forgetSpell(const std::string& spell) {
	std::map<std::string, ASpell*>::iterator it = _spells.find(spell);
	if (it != _spells.end()) {
		delete it->second;
		_spells.erase(spell);
	}
}

void Warlock::launchSpell(const std::string& spell, const ATarget& target) {
	std::map<std::string, ASpell*>::iterator it = _spells.find(spell);
	if (it != _spells.end())
		it->second->launch(target);
}
