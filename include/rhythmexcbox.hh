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

#ifndef BLOCKBOX_HH
#define BLOCKBOX_HH

#include "astream.hh"

#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/scale.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/combobox.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/liststore.h>
#include <gtkmm/alignment.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/checkbutton.h>

#include <gconfmm.h>

#include <string>
#include <list>

namespace gtkmmorsegui
{
    class BlockBox : public Gtk::VBox
    {
    public:
	BlockBox(Glib::RefPtr<Gnome::Conf::Client>);
	~BlockBox();

	sigc::signal<void, unsigned int>& signal_exercise_started();
	sigc::signal<void, std::list<std::string> >& signal_exercise_finished();
	
    private:
	Glib::RefPtr<Gnome::Conf::Client> m_conf_client;	

	libaudiostream::oastream* m_audioout;
	
	std::list< std::string > m_exercise_strings;

	Gtk::Frame m_frm_explanation;

	Gtk::Label m_lbl_explanation;
	Gtk::Button m_btn_play;

	Gtk::HButtonBox m_hbb_buttons;
	
	sigc::signal<void, unsigned int> m_started;
	sigc::signal<void, std::list<std::string> > m_finished;
	
	void on_btn_play_clicked();
    };
}

#endif

