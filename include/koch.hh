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

#ifndef KOCH_H
#define KOCH_H

#include "keyer.hh"
#include "skill.hh"

#include <string>
#include <list>

namespace libexercises
{
    const unsigned int addgroup = 0;
    const unsigned int addchar = 1;
    const unsigned int addsymbol = 2;
	
    
    class Koch
    {
	friend libkeyer::Keyer& operator<<(libkeyer::Keyer&, const Koch&);
	
    private:
	std::string m_strings;
	std::string m_chars;

	unsigned int m_num_chars;
	unsigned int m_num_strings;    
	unsigned int m_skill;

	unsigned int m_next_difficulty;

	std::string randstring(std::string, unsigned int);

    public:
//	Koch(unsigned int, unsigned int, unsigned int, unsigned int);	
	Koch(std::string, unsigned int, unsigned int, unsigned int, unsigned int);	
	Koch(const Koch&);
	~Koch();

	void shuffle();

	void next();
	
	std::list<std::string> stringtok() const;

	inline unsigned int skill() const
	{
	    return m_skill;
	}

	inline std::string get_chars() const
	{
	    return m_chars;
	}

	inline unsigned int strlen() const
	{
	    return m_num_chars;
	}

	inline unsigned int strnum() const
	{
	    return m_num_strings;
	}

	inline unsigned int difficulty() const
	{
	    return m_next_difficulty;
	}
    };

    libkeyer::Keyer& operator<<(libkeyer::Keyer&, const Koch&);
}
#endif //KOCH_H
