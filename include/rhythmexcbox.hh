// -*- C++ -*-
/***************************************************************************
                          GtkMMorse main window
                          ---------------------
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

#ifndef RHYTHMEXCBOX_HH
#define RHYTHMEXCBOX_HH

#include "astream.hh"

#include <gtkmm/scale.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>
#include <gtkmm/button.h>
#include <gtkmm/combobox.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/liststore.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/checkbutton.h>

#include <gconfmm.h>

#include <string>
#include <list>

namespace gtkmmorsegui
{
    class RhythmExcBox : public Gtk::VBox
    {
    public:
	RhythmExcBox(Glib::RefPtr<Gnome::Conf::Client>);
	~RhythmExcBox();

	sigc::signal<void, unsigned int>& signal_exercise_started();
	sigc::signal<void, std::list<std::string> >& signal_exercise_finished();
	
    private:
	Glib::RefPtr<Gnome::Conf::Client> m_conf_client;	

	libaudiostream::oastream* m_audioout;
	
	std::list< std::string > m_exercise_strings;

	Gtk::Frame m_frm_msg;
	Gtk::Label m_lbl_msg;
	
	Gtk::HButtonBox m_hbb_buttons;
	
	Gtk::Button m_btn_repeat;
	Gtk::Button m_btn_next;	
	Gtk::Button m_btn_start;
	Gtk::Button m_btn_stop;

	Gtk::HBox m_box_check;
	
	Gtk::Table m_tbl_check1;
	Gtk::Table m_tbl_check2;
	Gtk::Table m_tbl_check3;

	Gtk::Entry m_txt_check111;
	Gtk::Entry m_txt_check112;
	Gtk::Entry m_txt_check113;
	Gtk::Entry m_txt_check114;
	Gtk::Entry m_txt_check115;
	Gtk::Entry m_txt_check121;
	Gtk::Entry m_txt_check122;
	Gtk::Entry m_txt_check123;
	Gtk::Entry m_txt_check124;
	Gtk::Entry m_txt_check125;
	Gtk::Entry m_txt_check131;
	Gtk::Entry m_txt_check132;
	Gtk::Entry m_txt_check133;
	Gtk::Entry m_txt_check134;
	Gtk::Entry m_txt_check135;
	Gtk::Entry m_txt_check141;
	Gtk::Entry m_txt_check142;
	Gtk::Entry m_txt_check143;
	Gtk::Entry m_txt_check144;
	Gtk::Entry m_txt_check145;

	
	Gtk::Entry m_txt_check211;
	Gtk::Entry m_txt_check212;
	Gtk::Entry m_txt_check213;
	Gtk::Entry m_txt_check214;
	Gtk::Entry m_txt_check215;
	Gtk::Entry m_txt_check221;
	Gtk::Entry m_txt_check222;
	Gtk::Entry m_txt_check223;
	Gtk::Entry m_txt_check224;
	Gtk::Entry m_txt_check225;
	Gtk::Entry m_txt_check231;
	Gtk::Entry m_txt_check232;
	Gtk::Entry m_txt_check233;
	Gtk::Entry m_txt_check234;
	Gtk::Entry m_txt_check235;
	Gtk::Entry m_txt_check241;
	Gtk::Entry m_txt_check242;
	Gtk::Entry m_txt_check243;
	Gtk::Entry m_txt_check244;
	Gtk::Entry m_txt_check245;

	Gtk::Entry m_txt_check311;
	Gtk::Entry m_txt_check312;
	Gtk::Entry m_txt_check313;	
	Gtk::Entry m_txt_check314;
	Gtk::Entry m_txt_check315;
	Gtk::Entry m_txt_check321;	
	Gtk::Entry m_txt_check322;
	Gtk::Entry m_txt_check323;
	Gtk::Entry m_txt_check324;
	Gtk::Entry m_txt_check325;
	Gtk::Entry m_txt_check331;	
	Gtk::Entry m_txt_check332;
	Gtk::Entry m_txt_check333;
	Gtk::Entry m_txt_check334;
	Gtk::Entry m_txt_check335;
	Gtk::Entry m_txt_check341;	
	Gtk::Entry m_txt_check342;
	Gtk::Entry m_txt_check343;
	Gtk::Entry m_txt_check344;
	Gtk::Entry m_txt_check345;
	
	sigc::signal<void, unsigned int> m_started;
	sigc::signal<void, std::list<std::string> > m_finished;
	
	void on_btn_start_clicked();
	void on_play_finished();
    };
}

#endif
