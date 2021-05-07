#pragma once

# include <string>
# include <iostream>

# include "ATarget.hpp"

class BrickWall : public ATarget
{
	public:
		BrickWall();
		virtual ~BrickWall();

		BrickWall* clone() const;
};
