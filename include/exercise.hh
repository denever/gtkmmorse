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
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA*
 *                                                                         *
 ***************************************************************************/

#ifndef EXERCISE_H
#define EXERCISE_H

#include "skill.hh"
#include "keyer.hh"

#include <string>

namespace libexercises
{
    class Exercise
    {
    public:
	Exercise(): m_num_chars(0), m_num_strings(0), m_skill(0)
	{
	    m_strings.clear();
	}

	Exercise(unsigned int num, unsigned int numch, unsigned int s):
	    m_num_chars(numch), m_num_strings(num), m_skill(s)
	{}
	Exercise(const Exercise&);
	~Exercise();

	virtual bool execute()=0;

	inline unsigned int string_len() const 
	{
	    return m_num_chars;
	}

	inline unsigned int len() const
	{
	    return m_num_strings;
	}

	inline std::string get_string() const
	{
	    return m_strings;
	}
	
//	std::string stringtok();

	std::list<std::string> stringtok();
	
    protected:
	std::string m_strings;
	unsigned int m_num_chars;
	unsigned int m_num_strings;    
	unsigned int m_skill;
    };


    libkeyer::Keyer& operator<<(libkeyer::Keyer&, const Exercise&);
}

#endif //EXERCISE_H
