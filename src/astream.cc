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

#include "astream.hh"

#include <iostream>

#include <cmath>
#include <limits>

using namespace std;
using namespace libaudiostream;

int offset = numeric_limits<short>::max()/2 - 1;

oastream::oastream()
{
    m_phase = 0.0;
    m_thread = 0;    
    m_format.bits = 16;
    m_format.channels = 2;
    m_format.rate = 44100;
    m_format.byte_format = AO_FMT_LITTLE;

    ao_initialize();
}

oastream::oastream(size_type b, size_type sr, size_type ch, size_type bf)
{
    m_phase = 0.0;
    m_thread = 0;        
    m_format.bits = b;
    m_format.channels = ch;
    m_format.rate = sr;
    m_format.byte_format = bf;

    ao_initialize();    
}

oastream::oastream(const oastream& cpy)
{
    m_format = cpy.m_format;
}
    
oastream::~oastream()
{
    ao_shutdown();
}

sigc::signal<void>& oastream::play_finished()
{
    return m_finished;
}

void oastream::thread_function()
{
    unsigned int m_default_driver;
    ao_device* m_audio;

    if( (m_default_driver = ao_default_driver_id()) < 0)
	std::cerr << "There is no default driver."<<endl;
    
    m_audio = ao_open_live(m_default_driver, &m_format, 0);
    
    if(!m_audio)
	std::cerr << "Error opening device"<<endl;

    for(;;)
    {
	Glib::Mutex::Lock lock (m_mutex);

	if(m_queue.empty())
	    break;

	Wave w = m_queue.front();
	ao_play(m_audio, w.data, w.size);

	delete [] w.data;
	m_queue.pop();
    }

    if (m_audio)
	ao_close(m_audio);
    
    m_finished();
}

void oastream::play()
{
    if(m_thread)
	return;
    m_thread = Glib::Thread::create(sigc::mem_fun(*this, &oastream::thread_function), true);
}

void oastream::enqueue_sine(size_type millisecond, double frequency)
{
    size_type sample_number = millisecond * m_format.rate/1000;

    size_type len =  m_format.bits/8 * m_format.channels * sample_number;

    samples_buffer_pointer buffer = new char[len];
    
    for(unsigned int i = 0; i < sample_number; i++)
    {
	int sample = (int)(0.75 * 32768.0 * sin(2 * M_PI * frequency * ((float) i/m_format.rate)));

	unsigned int rt = 30;     //rise-time   (inspired by qrq)
	unsigned int ft = 30;     //fall-time   (inspired by qrq)

	if ( i < rt ) { sample *= sin(M_PI*i/(2.0*rt)); }

	if ( i > (sample_number - ft) ) { sample *= sin(2*M_PI*(i- (sample_number - ft) +ft)/(4.0*ft)) ; }

	buffer[4*i] = buffer[4*i+2] = sample & 0xff;
	buffer[4*i+1] = buffer[4*i+3] = (sample >> 8) & 0xff;
    }
    
    Wave tmp(len, buffer);

    Glib::Mutex::Lock lock (m_mutex);
    
    m_queue.push(tmp);
}

void oastream::enqueue_pause(size_type millisecond)
{
    size_type sample_number = millisecond * m_format.rate/1000;

    size_type len =  m_format.bits/8 * m_format.channels * sample_number;

    samples_buffer_pointer buffer = new char[len];
    
    for(unsigned int i = 0; i<sample_number; i++)
    {
	buffer[4*i] = buffer[4*i+2] = 0;
	buffer[4*i+1] = buffer[4*i+3] = 0;
    }
    
    Wave tmp(len, buffer);

    Glib::Mutex::Lock lock (m_mutex);
    
    m_queue.push(tmp);
}
