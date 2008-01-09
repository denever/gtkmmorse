// -*- C++ -*-
/***************************************************************************
                           GtkMMorse gui
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

#include "blocks.hh"
#include "rhythmexcbox.hh"
#include "resources.hh"

using namespace gtkmmorsegui;

RhythmExcBox::RhythmExcBox(Glib::RefPtr<Gnome::Conf::Client> conf_client):
    m_conf_client(conf_client),
    m_frm_msg("Koch exercise"),
    m_lbl_msg(rhythmexc_explanation),
    m_btn_repeat("repeat"),
    m_btn_next("next"),
    m_btn_start("start"),
    m_btn_stop("stop")
{
    m_frm_msg.add(m_lbl_msg);

    m_lbl_msg.set_line_wrap();

    pack_start(m_frm_msg);
    
    m_btn_repeat.set_sensitive(false);
    m_btn_next.set_sensitive(false);    
    m_btn_start.set_sensitive(true);
    m_btn_stop.set_sensitive(false);

    m_hbb_buttons.add(m_btn_repeat);
    m_hbb_buttons.add(m_btn_next);    
    m_hbb_buttons.add(m_btn_stop);
    m_hbb_buttons.add(m_btn_start);
    
    pack_start(m_hbb_buttons);
    
    m_btn_start.signal_clicked().connect( sigc::mem_fun(*this, &RhythmExcBox::on_btn_start_clicked) );
}

RhythmExcBox::~RhythmExcBox()
{}

sigc::signal<void, unsigned int>& RhythmExcBox::signal_exercise_started()
{
    return m_started;
}

sigc::signal<void, std::list<std::string> >& RhythmExcBox::signal_exercise_finished()
{
    return m_finished;
}

void RhythmExcBox::on_btn_start_clicked()
{
    m_btn_start.set_sensitive(false);

    unsigned int begin_pause = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/beginpause");
    unsigned int keyspeed = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/keyspeed");
    unsigned int charpause = 3;
    unsigned int strpause = 12;
    unsigned int strnum = 12;

    m_started.emit(strnum);

    m_audioout = new libaudiostream::oastream();

    m_audioout->play_finished().connect( sigc::mem_fun(*this, &RhythmExcBox::on_play_finished) );
    
    libkeyer::Keyer current_keyer(m_audioout, keyspeed, charpause, strpause, 900, 850);

    libexercises::Blocks rhythm_exc(strnum, libexercises::skill5, 5);

    m_exercise_strings = rhythm_exc.stringtok();
    
    m_audioout->enqueue_pause(begin_pause*1000);
    
    current_keyer << rhythm_exc;
    
    m_audioout->play();

    m_audioout->enqueue_pause(begin_pause*1000);
}

void RhythmExcBox::on_play_finished()
{
    delete m_audioout;
    m_btn_start.set_sensitive(true);
    m_finished.emit(m_exercise_strings);    
}
