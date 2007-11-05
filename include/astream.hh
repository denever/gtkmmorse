// -*- C++ -*-
/***************************************************************************
                         liboutputaudiothreaded
                          --------------------
    Copyright (C) 2007 Giuseppe "denever" Martino
    begin                : Fri 30 Mar 2007
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

#ifndef AUDIOSTREAM_H
#define AUDIOSTREAM_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <ao/ao.h>
#include <queue>
#include <glibmm/thread.h>
#include <glibmm/dispatcher.h>


namespace libaudiostream
{
    typedef char* samples_buffer_pointer;
    typedef char sample_type;
    typedef unsigned int size_type;

    struct Wave
    {
    public:
	Wave(size_type s, samples_buffer_pointer d):
	    data(d), size(s)
	{}
	samples_buffer_pointer data;
	size_type size;
    };
    
    class oastream: public sigc::trackable
    {
    public:
	oastream();
	oastream(size_type, size_type, size_type, size_type);
	oastream(const oastream&);
	~oastream();

	void enqueue_sine(size_type, double);
	void enqueue_pause(size_type);
	void play();
	void thread_function();

	sigc::signal<void>& play_finished();
	
    private:
	double m_phase;
	ao_sample_format m_format;

	std::queue<Wave> m_queue;
	
	Glib::Thread* m_thread;
	Glib::Mutex m_mutex;

	sigc::signal<void>   m_finished;
    };
}

#endif //AUDIOSTREAM_H
