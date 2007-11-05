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

#include "exercise.hh"

using namespace std;
using namespace libexercises;

Exercise::Exercise(const Exercise& cpy)
{
    m_strings = cpy.m_strings;
}

Exercise::~Exercise()
{
}

std::list< std::string > Exercise::stringtok()
{
    typedef string::const_iterator c_str; 
    unsigned int i = 0;

    list<string> tmplst;
    string tmp;
    
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

libkeyer::Keyer& libexercises::operator<<(libkeyer::Keyer& out, const Exercise& exc)
{
    unsigned int strlen = exc.string_len();

    for(unsigned int i=0; i< exc.len(); i++)
	out << exc.get_string().substr(i* strlen, strlen);

    return out;
}
