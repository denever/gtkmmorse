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
#ifndef AUDIOEXCEPTION_H
#define AUDIOEXCEPTION_H

#include <string>
#include <exception>

namespace libaudiostream
{
    class AudioException : public std::exception
    {

    private:
	std::string m_message;

    public:
	AudioException(const std::string &message) throw() : std::exception()
	{
	    m_message = message;
	}

	virtual ~AudioException() throw() 
	{
	}

	virtual const char* message() const throw()
	{
	    return m_message.c_str();
	}

    };
}

#endif // AUDIOEXCEPTION_H
