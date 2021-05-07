#pragma once

# include <string>
# include <iostream>

# include "ATarget.hpp"

class Dummy : public ATarget
{
	public:
		Dummy();
		virtual ~Dummy();

		virtual Dummy* clone() const;
};
