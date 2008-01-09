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
		      unsigned int=2, unsigned int=900, unsigned int=900);

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
	
	inline unsigned int dah_tone() const
	{
	    return int(m_dah_tone);
	}

	inline unsigned int dih_tone() const
	{
	    return int(m_dih_tone);
	}
	
    private:
	libaudiostream::oastream* m_audio;

	unsigned int m_speed;
	unsigned int m_count;
	unsigned int m_interch;
	unsigned int m_interword;

	double m_dah_tone;
	double m_dih_tone;	

	void play(unsigned int, double);
	void char_pause();
	void string_pause();
    };
}

#endif // KEYER_H


