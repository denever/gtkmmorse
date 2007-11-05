// -*- C++ -*-
/***************************************************************************
    Copyright (C) 2007 Giuseppe "denever" Martino
    email                : denever@users.sourceforge.net
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program; if not, write to the Free Software            *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,             *
 *  MA 02110-1301 USA                                                      *
 *                                                                         *
 ***************************************************************************/

#ifndef BLOCKS_H
#define BLOCKS_H

#include "exercise.hh"
#include "skill.hh"

#include <string>

namespace libexercises
{
    class Blocks: public Exercise
    {
    public:
	Blocks(unsigned int, unsigned int, unsigned int);	
	Blocks(const Blocks&);
	~Blocks();

    private:
	void m_prepare_mixed();
	void m_prepare_submixed();
	void m_prepare_ordered();	
	unsigned int share();
	std::string randstring(std::string, unsigned int);
	std::string gen(std::string, unsigned int);

	bool execute();
    };
}
#endif //BLOCKS_H
