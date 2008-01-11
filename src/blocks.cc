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

#include "blocks.hh"
#include "random.hh"

using namespace libexercises;

// give a random string from input
std::string Blocks::randstring(std::string input, unsigned int num)
{
    unsigned int size = input.size();

    librandom::Random RND;

    std::string output;
    output.clear();

    while(num != 0)
    {
	unsigned int pos = RND.integer(0, size-1);

	output += input[pos];	
	num--;
    }

    return output;
}

Blocks::Blocks(): m_num_chars(0), m_num_strings(0)
{
    m_strings.clear();
}

Blocks::Blocks(unsigned int num, std::string symbols, unsigned int numch): m_num_chars(numch), m_num_strings(num)
{
    m_strings = randstring(symbols, m_num_chars * m_num_strings);
}

Blocks::Blocks(const Blocks& cpy)
{
    m_strings = cpy.m_strings;
}

Blocks::~Blocks()
{
    m_strings.clear();
}

std::list< std::string > Blocks::stringtok()
{
    typedef std::string::const_iterator c_str; 
    unsigned int i = 0;

    std::list< std::string > tmplst;
    std::string tmp;
    
    for(c_str it = m_strings.begin(); it != m_strings.end(); it++) 
    {
	if(i == m_num_chars)
	{
	    tmplst.push_back(tmp);
	    tmp.clear();
	    i = 0;
	}
	tmp.push_back(*it);
	i++;
    }

    tmplst.push_back(tmp);
    tmp.clear();
	  
    return tmplst;
}

libkeyer::Keyer& libexercises::operator<<(libkeyer::Keyer& out, const Blocks& exc)
{
    unsigned int strlen = exc.string_len();

    for(unsigned int i=0; i< exc.len(); i++)
	out << exc.get_string().substr(i* strlen, strlen);

    return out;
}
