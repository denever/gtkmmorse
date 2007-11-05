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

#ifndef KEYER_H
#define KEYER_H

#include "astream.hh"

#include <string>

namespace libkeyer
{
    class Keyer
    {
    public:
	explicit Keyer(libaudiostream::oastream*, unsigned int, unsigned int =3,
		      unsigned int=2, unsigned int=1, unsigned int=3);

	Keyer(const Keyer&);
	Keyer& operator<<(const unsigned int&);
	Keyer& operator<<(unsigned char);
	Keyer& operator<<(const std::string&);

	void set_speed(unsigned int);
	void set_charpause_len(unsigned int);
	void set_stringpause_len(unsigned int);
	void set_dot_len(unsigned int);
	void set_line_len(unsigned int);

	inline unsigned int keying_speed()
	{
	    return m_speed;
	}

	inline unsigned int charpause_len()
	{
	    return m_interch;
	}

	inline unsigned int stringpause_len()
	{
	    return m_interword;
	}

	inline unsigned int dot_len() const
	{
	    return m_dot;
	}

	inline unsigned int line_len() const
	{
	    return m_line;
	}
	
	inline unsigned int tone() const
	{
	    return int(m_tone);
	}

	inline void set_tone(unsigned int t)
	{
	    m_tone = t;
	}
	
    private:
	libaudiostream::oastream* m_audio;

	unsigned int m_speed;
	unsigned int m_count;
	unsigned int m_interch;
	unsigned int m_interword;

	double m_tone;

	unsigned int m_dot;
	unsigned int m_line;

	void play(unsigned int);
	void char_pause();
	void string_pause();
    };
}

#endif // KEYER_H


