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

#include "koch.hh"
#include "random.hh"

using namespace std;
using namespace libexercises;

// give a random string from input
string Koch::randstring(string input, unsigned int num)
{
    unsigned int size = input.size();

    librandom::Random RND;

    string output;
    output.clear();

    while(num!=0)
    {
	unsigned int pos = RND.integer(0, size-1);
        output += input[pos];
        num--;
    }

    return output;
}

Koch::Koch(string str, unsigned int num, unsigned int numch, unsigned int s, unsigned int d): 
    m_chars(str), m_num_chars(numch), m_num_strings(num), m_skill(s), m_next_difficulty(d)
{
    m_strings = randstring(m_chars.substr(0, m_skill), m_num_chars * m_num_strings);
}

Koch::Koch(const Koch& cpy)
{
    m_strings = cpy.m_strings;
}

Koch::~Koch()
{
    m_strings.clear();
}

void Koch::shuffle()
{
    m_strings = randstring(m_chars.substr(0, m_skill), m_num_chars * m_num_strings);
}

void Koch::next()
{
    switch(m_next_difficulty)
    {
    case addgroup:
    {
	m_num_strings++;
	m_next_difficulty = addchar;
	break;
    }
    case addchar:
    {
	m_num_chars++;
	m_next_difficulty = addsymbol;
	break;
    }
    case addsymbol:
    {
	m_skill++;
	m_next_difficulty = addgroup;
	break;
    }
    }
    
    m_strings = randstring(m_chars.substr(0, m_skill), m_num_chars * m_num_strings);
}

libkeyer::Keyer& libexercises::operator<<(libkeyer::Keyer& out, const Koch& exc)
{
    std::list<std::string> lks = exc.stringtok();
    typedef std::list< std::string >::const_iterator c_str;
    
    for(c_str lks_it = lks.begin(); lks_it != lks.end(); lks_it++)
	out << *lks_it;

    return out;		
}

std::list<std::string> Koch::stringtok() const
{
    std::list<std::string> tmp_list;
    string tmp_str;
    unsigned int count = 0;

    for(unsigned i=0; i < m_strings.size(); ++i)
    {	
	if(count == m_num_chars)
	{
	    tmp_list.push_back(tmp_str);
	    tmp_str.clear();
	    count = 0;
	}
	tmp_str += m_strings[i];
	count++;
    }

    tmp_list.push_back(tmp_str);

    return tmp_list;
}
