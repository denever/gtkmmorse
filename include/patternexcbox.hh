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

#ifndef PATTERNEXCBOX_HH
#define PATTERNEXCBOX_HH

#include "astream.hh"
#include "bicheckbuttons.hh"

#include <gtkmm/scale.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/separator.h>

#include <gconfmm.h>

#include <string>
#include <list>

namespace gtkmmorsegui
{
    class PatternExcBox : public Gtk::VBox
    {
    public:
	PatternExcBox(Glib::RefPtr<Gnome::Conf::Client>);
	~PatternExcBox();

	sigc::signal<void, unsigned int>& signal_exercise_started();
	sigc::signal<void, std::list<std::string> >& signal_exercise_finished();
	sigc::signal<void, std::list<std::string> >& signal_firstpattern_finished();
	sigc::signal<void, std::list<std::string> >& signal_seconpattern_finished();	
	
    private:
	Glib::RefPtr<Gnome::Conf::Client> m_conf_client;	

	libaudiostream::oastream* m_audioout;
	
	std::list< std::string > m_exercise_strings;

	Gtk::Frame m_frm_msg;
	Gtk::Frame m_frm_checkboard;	

	Gtk::Label m_lbl_msg;
	Gtk::Label m_lbl_firstpattern;
	Gtk::Label m_lbl_seconpattern;
	
	Gtk::HButtonBox m_hbb_buttons;
	
	Gtk::Button m_btn_firstpattern;
	Gtk::Button m_btn_seconpattern;
	Gtk::Button m_btn_start;

	Gtk::HBox m_box_check;
	Gtk::VBox m_box_lbls;	

	Gtk::VSeparator m_vsp_1;
	Gtk::VSeparator m_vsp_2;	
	
	Gtk::Table m_tbl_check1;
	Gtk::Table m_tbl_check2;
	Gtk::Table m_tbl_check3;
	Gtk::Table m_tbl_lbls;

//	Gtk::ProgressBar m_prb_overall;	
	
	gtkmmorsegui::BiCheckButtons m_rbt_check[3][4][5];	
	
	sigc::signal<void, unsigned int> m_started;
	sigc::signal<void, std::list<std::string> > m_finished;

	void on_btn_start_clicked();
	void on_btn_firstpattern_clicked();
	void on_btn_seconpattern_clicked();

	void on_play_finished();
	void on_firstpattern_finished();
	void on_seconpattern_finished();	    
    };
}

#endif
