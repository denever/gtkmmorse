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
#include "patternexcbox.hh"
#include "resources.hh"

using namespace gtkmmorsegui;

PatternExcBox::PatternExcBox(Glib::RefPtr<Gnome::Conf::Client> conf_client):
    m_conf_client(conf_client),
    m_frm_msg("Exercise explanation"),
    m_frm_checkboard("Check board"),    
    m_lbl_msg(patternexc_explanation),
    m_btn_firstpattern("Listen first pattern"),
    m_btn_seconpattern("Listen second pattern"),    
    m_btn_start("Start"),
    m_tbl_check1(4,5),
    m_tbl_check2(4,5),
    m_tbl_check3(4,5)   
{
    m_frm_msg.add(m_lbl_msg);

    m_lbl_msg.set_line_wrap();

    pack_start(m_frm_msg);
    
    m_btn_start.set_sensitive(true);
    m_frm_checkboard.set_sensitive(false);    

    m_hbb_buttons.add(m_btn_firstpattern);
    m_hbb_buttons.add(m_btn_seconpattern);
    m_hbb_buttons.add(m_btn_start);
    
    pack_start(m_hbb_buttons);

    m_btn_firstpattern.signal_clicked().connect( sigc::mem_fun(*this, &PatternExcBox::on_btn_firstpattern_clicked) );    
    m_btn_seconpattern.signal_clicked().connect( sigc::mem_fun(*this, &PatternExcBox::on_btn_seconpattern_clicked) );
    
    m_btn_start.signal_clicked().connect( sigc::mem_fun(*this, &PatternExcBox::on_btn_start_clicked) );

    for(unsigned int i = 0; i < 4; i++)
	for(unsigned int j = 0; j < 5; j++)
	    m_tbl_check1.attach(m_txt_check[0][i][j], j, j+1, i, i+1, Gtk::SHRINK, Gtk::SHRINK);

    for(unsigned int i = 0; i < 4; i++)
	for(unsigned int j = 0; j < 5; j++)
	    m_tbl_check2.attach(m_txt_check[1][i][j], j, j+1, i, i+1, Gtk::SHRINK, Gtk::SHRINK);
    
    for(unsigned int i = 0; i < 4; i++)
	for(unsigned int j = 0; j < 5; j++)
	    m_tbl_check3.attach(m_txt_check[2][i][j], j, j+1, i, i+1, Gtk::SHRINK, Gtk::SHRINK);

    m_box_check.pack_start(m_tbl_check1);
    m_box_check.pack_start(m_tbl_check2);
    m_box_check.pack_start(m_tbl_check3);
    
    m_frm_checkboard.add(m_box_check);

    pack_start(m_frm_checkboard, Gtk::PACK_SHRINK);
}

PatternExcBox::~PatternExcBox()
{}

sigc::signal<void, unsigned int>& PatternExcBox::signal_exercise_started()
{
    return m_started;
}

sigc::signal<void, std::list<std::string> >& PatternExcBox::signal_exercise_finished()
{
    return m_finished;
}

void PatternExcBox::on_btn_firstpattern_clicked()
{
    m_btn_start.set_sensitive(false);
    m_btn_firstpattern.set_sensitive(false);
    m_btn_seconpattern.set_sensitive(false);    

    unsigned int keyspeed = 12;
    unsigned int charpause = 3;
    unsigned int strpause = 12;
    unsigned int strnum = 12;

    m_started.emit(strnum);

    m_audioout = new libaudiostream::oastream();

    m_audioout->play_finished().connect( sigc::mem_fun(*this, &PatternExcBox::on_firstpattern_finished) );
    
    libkeyer::Keyer current_keyer(m_audioout, keyspeed, charpause, strpause, 900, 850);
    
    m_audioout->enqueue_pause(1000);
    
    current_keyer << (unsigned char)'f';
    
    m_audioout->play();

    m_audioout->enqueue_pause(1000);
}

void PatternExcBox::on_btn_seconpattern_clicked()
{
    m_btn_start.set_sensitive(false);
    m_btn_firstpattern.set_sensitive(false);
    m_btn_seconpattern.set_sensitive(false);    

    unsigned int keyspeed = 12;
    unsigned int charpause = 3;
    unsigned int strpause = 12;
    unsigned int strnum = 12;

    m_started.emit(strnum);

    m_audioout = new libaudiostream::oastream();

    m_audioout->play_finished().connect( sigc::mem_fun(*this, &PatternExcBox::on_seconpattern_finished) );
    
    libkeyer::Keyer current_keyer(m_audioout, keyspeed, charpause, strpause, 900, 850);
    
    m_audioout->enqueue_pause(1000);
    
    current_keyer << (unsigned char)'h';
    
    m_audioout->play();

    m_audioout->enqueue_pause(1000);
}

void PatternExcBox::on_btn_start_clicked()
{
    m_btn_start.set_sensitive(false);
    m_frm_checkboard.set_sensitive(true);

    unsigned int begin_pause = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/beginpause");
    unsigned int keyspeed = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/keyspeed");
    unsigned int charpause = 3;
    unsigned int strpause = 12;
    unsigned int strnum = 12;

    m_started.emit(strnum);

    m_audioout = new libaudiostream::oastream();

    m_audioout->play_finished().connect( sigc::mem_fun(*this, &PatternExcBox::on_play_finished) );
    
    libkeyer::Keyer current_keyer(m_audioout, keyspeed, charpause, strpause, 900, 850);

    libexercises::Blocks pattern_exc(strnum, libexercises::skill5, 5);

    m_exercise_strings = pattern_exc.stringtok();
    
    m_audioout->enqueue_pause(begin_pause*1000);
    
    current_keyer << pattern_exc;
    
    m_audioout->play();

    m_audioout->enqueue_pause(begin_pause*1000);
}

void PatternExcBox::on_play_finished()
{
    delete m_audioout;
    m_btn_start.set_sensitive(true);
    m_btn_firstpattern.set_sensitive(true);
    m_btn_seconpattern.set_sensitive(true);    
    m_finished.emit(m_exercise_strings);    
}

void PatternExcBox::on_firstpattern_finished()
{
    delete m_audioout;
    m_btn_start.set_sensitive(true);
    m_btn_firstpattern.set_sensitive(true);
    m_btn_seconpattern.set_sensitive(true);    
    m_finished.emit(m_exercise_strings);    
}

void PatternExcBox::on_seconpattern_finished()
{
    delete m_audioout;
    m_btn_start.set_sensitive(true);
    m_btn_firstpattern.set_sensitive(true);
    m_btn_seconpattern.set_sensitive(true);    
    m_finished.emit(m_exercise_strings);    
}
