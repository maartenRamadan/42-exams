#pragma once

# include <string>
# include <iostream>

# include "ASpell.hpp"

class ASpell;

class ATarget
{
	protected:
		std::string type;

		ATarget();

	private:
		ATarget(const ATarget& rhs);
		ATarget& operator=(const ATarget& rhs);

	public:
		ATarget(const std::string& type);
		virtual ~ATarget();

		void getHitBySpell(const ASpell& spell) const;
		const std::string& getType() const;
		virtual ATarget* clone() const = 0;

};
