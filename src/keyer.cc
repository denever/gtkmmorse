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

#include "keyer.hh"

using namespace libkeyer;
using namespace libaudiostream;
using namespace std;

// Scrivere qui qualcosa che spieghi...

typedef unsigned int morse_symbol;

static const morse_symbol map[] = 
{
// Letters
    0x8002, 0x7004, 0x5004, 0x6003, 0x8001, 0xD004, 0x2003,
    0xF004, 0xC002, 0x8004, 0x4003, 0xB004, 0x0002, 0x4002,
    0x0003, 0x9004, 0x2004, 0xA003, 0xE003, 0x0001, 0xC003,
    0xE004, 0x8003, 0x6004, 0x4004, 0x3004,
   
// Numbers in morse code from map[26]
    0x0005, 0x8005, 0xC005, 0xE005, 0xF005, 0xF805, 0x7805,
    0x3805, 0x1805, 0x0805
};

const unsigned int dih = 1;
const unsigned int dah = 3;

Keyer::Keyer(oastream* audio, unsigned int speed, unsigned int ch, unsigned int wd, unsigned int dih_tone, unsigned int dah_tone)
    :  m_audio(audio), m_speed(speed), m_interch(ch), m_interword(wd), m_dih_tone(dih_tone), m_dah_tone(dah_tone)
{
    unsigned int dpm = m_speed*((36 + 4 * m_interch + m_interword)*dih);
    m_count = int(60000/dpm);
}

void Keyer::set_speed(unsigned int speed)
{
    m_speed = speed;
    unsigned int dpm = m_speed*((36 + 4 * m_interch + m_interword)*dih);
    m_count = int(60000/dpm);
}

void Keyer::set_charpause_len(unsigned int len)
{   
    m_interch = len;
    unsigned int dpm = m_speed*((36 + 4 * m_interch + m_interword)*dih);
    m_count = int( 60000/dpm );
}

void Keyer::set_stringpause_len(unsigned int len)
{    
    m_interword = len;
    unsigned int dpm = m_speed*((36 + 4 * m_interch + m_interword)*dih);
    m_count = int( 60000/dpm );
}

void Keyer::play(unsigned int n, double tone)
{
    m_audio->enqueue_sine(m_count * n, tone);
    m_audio->enqueue_pause(m_count);
}   

Keyer& Keyer::operator<<(const morse_symbol& input)
{
    unsigned int data = input & 0xF800;
    unsigned int size = input & 0x000F;
    
    while(size != 0)
    {
	if( (data & 0x8000) == 0)
	    play(dah, m_dah_tone);

	if( (data & 0x8000) == 0x8000)
	    play(dih, m_dih_tone);

	data = data << 1;

	size--;
    }

    return *this;
}

Keyer& Keyer::operator<<(unsigned char ch)
{
    if( (ch > 96) && (ch < 123))
	ch -= 97;
    
    if( (ch >47) && (ch < 58))
	ch -= 22;               // -48 + 26 = -22

    if(ch < 36) // bound of array
	*this<<morse_symbol(map[ch]);

    return *this;
}

Keyer& Keyer::operator<<(const std::string& input)
{
    typedef std::string::const_iterator cit;

    for(cit it = input.begin(); it!=input.end(); it++)
    {
	unsigned char ch = *it;
	*this<<ch;
	char_pause();
    }
    
    string_pause();

    return *this;		
}
    
void Keyer::char_pause()
{
    m_audio->enqueue_pause(m_count*m_interch); // ugly kludge
}

void Keyer::string_pause()
{
    m_audio->enqueue_pause(m_count*m_interword); // ugly kludge
}
