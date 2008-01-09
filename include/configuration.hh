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

class Configuration
{
public:
    Configuration();
    ~Configuration();

    void set_beginpause(unsigned int);
    unsigned int get_beginpause();
    void set_keyingspeed(unsigned int);
    unsigned int get_keyingspeed();
    void set_charpause(unsigned int);
    unsigned int get_charpause();
    void set_stringpause(unsigned int);
    unsigned int get_stringpause();
    void set_linelength(unsigned int);
    unsigned int get_linelength();
    void set_pitch(unsigned int);
    unsigned int get_pitch();


private:
    unsigned int m_beginpause;
    unsigned int m_keyingspeed;
    unsigned int m_charpause;
    unsigned int m_stringpause;
    unsigned int m_linelength;
    unsigned int m_pitch;
};

