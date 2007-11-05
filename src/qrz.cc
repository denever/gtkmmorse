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

#include "qrz.hh"
#include "random.hh"

using namespace std;
using namespace libexercises;

Qrz::Qrz(const Qrz& cpy)
{
    m_strings = cpy.m_strings;
}

Qrz::Qrz(const string& qrz_format, unsigned int qrz_num): Exercise(qrz_num, qrz_format.size(), 0)
{
    string group_chars("eishtmoawjuvrlpfndbgkcyqzx");
    string group_numbrs("0123456789");

    librandom::Random RND;

    string buffer;
    buffer.clear();

    typedef std::string::const_iterator cit;

    for(unsigned int i=0; i<m_num_strings; i++)
    {
	for(cit it = qrz_format.begin(); it!= qrz_format.end(); it++)
	    switch(*it)
	    {
	    case '@':
		m_strings += group_chars[ RND.integer(0, group_chars.size()-1)];
		break;

	    case '#':
		m_strings += group_numbrs[ RND.integer(0, group_numbrs.size()-1)];
		break;

	    case '?':
		if(RND.integer(0,1))
		    m_strings += group_chars[RND.integer(0, group_chars.size()-1)];
		break;

	    case '$':
		if(RND.integer(0,1))
		    m_strings += group_numbrs[RND.integer(0, group_numbrs.size()-1)];
		break;

	    default:
		m_strings += *it;
	    }

	unsigned int temp = (i+1)*m_num_chars - m_strings.size();
	
	for(unsigned int j = 0; j < temp; j++)
	    m_strings += " ";
    }
}

bool Qrz::execute()
{
    return true;
}
