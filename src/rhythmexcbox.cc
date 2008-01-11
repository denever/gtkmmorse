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
    m_frm_msg("Rhythm exercise"),
    m_lbl_msg(rhythmexc_explanation),
    m_btn_repeat("repeat"),
    m_btn_next("next"),
    m_btn_start("start"),
    m_btn_stop("stop"),
    m_tbl_check1(4,5),
    m_tbl_check2(4,5),
    m_tbl_check3(4,5)   
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
    
    m_txt_check111.set_width_chars(1);
    m_txt_check112.set_width_chars(1);
    m_txt_check113.set_width_chars(1);
    m_txt_check114.set_width_chars(1);
    m_txt_check115.set_width_chars(1);

    m_txt_check121.set_width_chars(1);
    m_txt_check122.set_width_chars(1);
    m_txt_check123.set_width_chars(1);
    m_txt_check124.set_width_chars(1);
    m_txt_check125.set_width_chars(1);

    m_txt_check131.set_width_chars(1);
    m_txt_check132.set_width_chars(1);
    m_txt_check133.set_width_chars(1);	
    m_txt_check134.set_width_chars(1);
    m_txt_check135.set_width_chars(1);

    m_txt_check141.set_width_chars(1);
    m_txt_check142.set_width_chars(1);
    m_txt_check143.set_width_chars(1);	
    m_txt_check144.set_width_chars(1);
    m_txt_check145.set_width_chars(1);

    m_txt_check211.set_width_chars(1);
    m_txt_check212.set_width_chars(1);
    m_txt_check213.set_width_chars(1);
    m_txt_check214.set_width_chars(1);
    m_txt_check215.set_width_chars(1);

    m_txt_check221.set_width_chars(1);
    m_txt_check222.set_width_chars(1);
    m_txt_check223.set_width_chars(1);
    m_txt_check224.set_width_chars(1);
    m_txt_check225.set_width_chars(1);

    m_txt_check231.set_width_chars(1);	
    m_txt_check232.set_width_chars(1);
    m_txt_check233.set_width_chars(1);
    m_txt_check234.set_width_chars(1);
    m_txt_check235.set_width_chars(1);

    m_txt_check241.set_width_chars(1);	
    m_txt_check242.set_width_chars(1);
    m_txt_check243.set_width_chars(1);
    m_txt_check244.set_width_chars(1);
    m_txt_check245.set_width_chars(1);

    m_txt_check311.set_width_chars(1);
    m_txt_check312.set_width_chars(1);
    m_txt_check313.set_width_chars(1);
    m_txt_check314.set_width_chars(1);
    m_txt_check315.set_width_chars(1);

    m_txt_check321.set_width_chars(1);
    m_txt_check322.set_width_chars(1);
    m_txt_check323.set_width_chars(1);
    m_txt_check324.set_width_chars(1);
    m_txt_check325.set_width_chars(1);

    m_txt_check331.set_width_chars(1);	
    m_txt_check332.set_width_chars(1);
    m_txt_check333.set_width_chars(1);
    m_txt_check334.set_width_chars(1);
    m_txt_check335.set_width_chars(1);

    m_txt_check341.set_width_chars(1);	
    m_txt_check342.set_width_chars(1);
    m_txt_check343.set_width_chars(1);
    m_txt_check344.set_width_chars(1);
    m_txt_check345.set_width_chars(1);

    m_tbl_check1.attach(m_txt_check111, 0, 1, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check112, 1, 2, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check113, 2, 3, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check114, 3, 4, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check115, 4, 5, 0, 1, Gtk::SHRINK, Gtk::SHRINK);

    m_tbl_check1.attach(m_txt_check121, 0, 1, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check122, 1, 2, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check123, 2, 3, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check124, 3, 4, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check125, 4, 5, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
    
    m_tbl_check1.attach(m_txt_check131, 0, 1, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check132, 1, 2, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check133, 2, 3, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check134, 3, 4, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check135, 4, 5, 2, 3, Gtk::SHRINK, Gtk::SHRINK);

    m_tbl_check1.attach(m_txt_check141, 0, 1, 3, 4, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check142, 1, 2, 3, 4, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check143, 2, 3, 3, 4, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check144, 3, 4, 3, 4, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check1.attach(m_txt_check145, 4, 5, 3, 4, Gtk::SHRINK, Gtk::SHRINK);

    m_box_check.pack_start(m_tbl_check1);
    
    m_tbl_check2.attach(m_txt_check211, 0, 1, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check2.attach(m_txt_check212, 1, 2, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check2.attach(m_txt_check213, 2, 3, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check2.attach(m_txt_check214, 3, 4, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check2.attach(m_txt_check215, 4, 5, 0, 1, Gtk::SHRINK, Gtk::SHRINK);

    m_tbl_check2.attach(m_txt_check221, 0, 1, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check2.attach(m_txt_check222, 1, 2, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check2.attach(m_txt_check223, 2, 3, 1, 2, Gtk::SHRINK, Gtk::SHRINK);	
    m_tbl_check2.attach(m_txt_check224, 3, 4, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check2.attach(m_txt_check225, 4, 5, 1, 2, Gtk::SHRINK, Gtk::SHRINK);

    m_tbl_check2.attach(m_txt_check231, 0, 1, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check2.attach(m_txt_check232, 1, 2, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check2.attach(m_txt_check233, 2, 3, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check2.attach(m_txt_check234, 3, 4, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check2.attach(m_txt_check235, 4, 5, 2, 3, Gtk::SHRINK, Gtk::SHRINK);

    m_tbl_check2.attach(m_txt_check241, 0, 1, 3, 4, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check2.attach(m_txt_check242, 1, 2, 3, 4, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check2.attach(m_txt_check243, 2, 3, 3, 4, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check2.attach(m_txt_check244, 3, 4, 3, 4, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check2.attach(m_txt_check245, 4, 5, 3, 4, Gtk::SHRINK, Gtk::SHRINK);

    m_box_check.pack_start(m_tbl_check2);

    m_tbl_check3.attach(m_txt_check311, 0, 1, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check3.attach(m_txt_check312, 1, 2, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check3.attach(m_txt_check313, 2, 3, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check3.attach(m_txt_check314, 3, 4, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check3.attach(m_txt_check315, 4, 5, 0, 1, Gtk::SHRINK, Gtk::SHRINK);

    m_tbl_check3.attach(m_txt_check321, 0, 1, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check3.attach(m_txt_check322, 1, 2, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check3.attach(m_txt_check323, 2, 3, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check3.attach(m_txt_check324, 3, 4, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check3.attach(m_txt_check325, 4, 5, 1, 2, Gtk::SHRINK, Gtk::SHRINK);

    m_tbl_check3.attach(m_txt_check331, 0, 1, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check3.attach(m_txt_check332, 1, 2, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check3.attach(m_txt_check333, 2, 3, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check3.attach(m_txt_check334, 3, 4, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check3.attach(m_txt_check335, 4, 5, 2, 3, Gtk::SHRINK, Gtk::SHRINK);

    m_tbl_check3.attach(m_txt_check341, 0, 1, 3, 4, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check3.attach(m_txt_check342, 1, 2, 3, 4, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check3.attach(m_txt_check343, 2, 3, 3, 4, Gtk::SHRINK, Gtk::SHRINK);	
    m_tbl_check3.attach(m_txt_check344, 3, 4, 3, 4, Gtk::SHRINK, Gtk::SHRINK);
    m_tbl_check3.attach(m_txt_check345, 4, 5, 3, 4, Gtk::SHRINK, Gtk::SHRINK);

    m_box_check.pack_start(m_tbl_check3);

    pack_start(m_box_check);
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
