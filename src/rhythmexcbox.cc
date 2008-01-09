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
#include "blockbox.hh"
#include "resources.hh"

#include <gconfmm.h>

using namespace gtkmmorsegui;

BlockBox::BlockBox(Glib::RefPtr<Gnome::Conf::Client> conf_client):
    m_conf_client(conf_client),
    m_frm_explanation(m_lbl_explanation),
    m_btn_play("start")
{
    m_lbl_explanation = rhythmexc_explanation;
    
    m_btn_play.set_sensitive(false);
    m_hbb_buttons.pack_start(m_btn_play);

    pack_start(m_frm_stringlength);    
    pack_start(m_frm_stringnum);
    pack_start(m_frm_charset);
    pack_start(m_hbb_buttons);
    
    m_btn_play.signal_clicked().connect( sigc::mem_fun(*this, &BlockBox::on_btn_play_clicked) );
    m_cmb_charset.signal_changed().connect( sigc::mem_fun(*this, &BlockBox::on_cmb_charset_changed) );
}

BlockBox::~BlockBox()
{}

sigc::signal<void, unsigned int>& BlockBox::signal_exercise_started()
{
    return m_started;
}

sigc::signal<void, std::list<std::string> >& BlockBox::signal_exercise_finished()
{
    return m_finished;
}

void BlockBox::on_btn_play_clicked()
{
    m_btn_play.set_sensitive(false);

    unsigned int begin_pause = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/beginpause");
    unsigned int tone = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/tone");
    unsigned int keyspeed = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/keyspeed");
    unsigned int charpause = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/charpause");
    unsigned int strpause = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/strpause");
    unsigned int linelen = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/linelen");    

    unsigned int strnum = (unsigned int) m_hsl_stringnum.get_value();
    unsigned int strlen = (unsigned int) m_hsl_stringlength.get_value();

    m_started.emit(strnum);

    m_audioout = new libaudiostream::oastream();

    m_audioout->play_finished().connect( sigc::mem_fun(*this, &BlockBox::on_play_finished) );
    
    libkeyer::Keyer current_keyer(m_audioout, keyspeed, charpause, strpause, 1, linelen);

    current_keyer.set_tone(tone);

    libexercises::Blocks blocks_exc(strnum, libexercises::skill5 | libexercises::submixed, strlen);

    m_exercise_strings = blocks_exc.stringtok();
    
    m_audioout->enqueue_pause(begin_pause*1000);
    
    current_keyer<<blocks_exc;
    
    m_audioout->play();

    m_audioout->enqueue_pause(begin_pause*1000);
}

void BlockBox::on_play_finished()
{
    delete m_audioout;
    m_btn_play.set_sensitive(true);
    m_finished.emit(m_exercise_strings);    
}
