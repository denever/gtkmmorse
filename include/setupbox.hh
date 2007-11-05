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

#ifndef SETUPBOX_HH
#define SETUPBOX_HH

#include <gtkmm/box.h>
#include <gtkmm/scale.h>
#include <gtkmm/frame.h>
#include <gtkmm/button.h>
#include <gtkmm/adjustment.h>

#include <gconfmm.h>

namespace gtkmmorsegui
{
    class SetupBox : public Gtk::VBox
    {
    public:
	SetupBox(Glib::RefPtr<Gnome::Conf::Client>);
	~SetupBox();

    private:
	Gtk::Frame m_frm_beginpause;
	Gtk::Frame m_frm_keyspeed;
	Gtk::Frame m_frm_charpause;
	Gtk::Frame m_frm_stringpause;
	Gtk::Frame m_frm_tone;
	Gtk::Frame m_frm_linelen;

	Gtk::Button m_btn_save;

	Gtk::HScale m_hsl_beginpause;
	Gtk::HScale m_hsl_keyspeed;
	Gtk::HScale m_hsl_charpause;
	Gtk::HScale m_hsl_stringpause;
	Gtk::HScale m_hsl_tone;
	Gtk::HScale m_hsl_linelen;

	Glib::RefPtr<Gnome::Conf::Client> m_conf_client;
	
	void on_btn_save_clicked();
	bool on_configuration_changed(Gtk::ScrollType, double);
    };
}

#endif

