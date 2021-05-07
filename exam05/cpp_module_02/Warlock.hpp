#pragma once

# include <string>
# include <iostream>
# include <map>

#include "ATarget.hpp"
#include "SpellBook.hpp"

class Warlock
{
	private:
		std::string _name;
		std::string _title;
		SpellBook _spells;

		Warlock();
		Warlock(const Warlock& rhs);
		Warlock& operator=(const Warlock& rhs);

	public:
		Warlock(const std::string& name, const std::string& title);
		~Warlock();

		const std::string& getName() const;
		const std::string& getTitle() const;

		void setTitle(const std::string& title);
		void introduce() const;

		void learnSpell(ASpell* spell);
		void forgetSpell(const std::string& spell);
		void launchSpell(const std::string& spell, const ATarget& target);
};
