// -*- C++ -*-
/***************************************************************************
                                 GtkMMorse
                          --------------------
    Copyright (C) 2007 Giuseppe "denever" Martino
    begin                : Fri 23 Mar 2007
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


Configuration::Configuration():
    m_beginpause(0),
    m_keyingspeed(0),
    m_charpause(0),
    m_stringpause(0),
    m_linelength(0),
    m_tone(0)
{}

void Configuration::beginpause(unsigned int v)
{
    m_beginpause = v;
}

unsigned int Configuration::beginpause()
{
    return m_beginpause;

}

void Configuration::keyingspeed(unsigned int v)
{
    m_keyingspeed = v;
}

unsigned int Configuration::keyingspeed()
{
    return m_keyingspeed;
}

void Configuration::charpause(unsigned int v)
{
    m_charpause = v;
}

unsigned int Configuration::charpause()
{
    return m_charpause;
}

void Configuration::stringpause(unsigned int v)
{
    m_stringpause = v;
}

unsigned int Configuration::stringpause()
{
    return m_stringpause;
}

void Configuration::linelength(unsigned int v)
{
    m_linelength = v;
}

unsigned int Configuration::linelength()
{
    return m_linelength;
}

void Configuration::tone(unsigned int v)
{
    m_tone = v;
}

unsigned int Configuration::tone()
{
    return m_tone;
}
