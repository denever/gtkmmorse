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

#ifndef KOCHSETUPBOX_HH
#define KOCHSETUPBOX_HH

#include <gtkmm/box.h>
#include <gtkmm/scale.h>
#include <gtkmm/frame.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/adjustment.h>

#include <gconfmm.h>

namespace gtkmmorsegui
{
    class KochSetupBox : public Gtk::VBox
    {
    public:
	KochSetupBox(Glib::RefPtr<Gnome::Conf::Client>);
	~KochSetupBox();

    private:
	Gtk::Frame m_frm_chars;
	Gtk::Frame m_frm_charitem;	
	Gtk::Frame m_frm_stringnumbers;
	Gtk::Frame m_frm_stringlength;
	Gtk::Frame m_frm_keyspeed;
	Gtk::Frame m_frm_skill;

	Gtk::Button m_btn_save;

	Gtk::Entry m_txt_chars;
	Gtk::HScale m_hsl_charitem;
	Gtk::HScale m_hsl_stringnumbers;
	Gtk::HScale m_hsl_stringlength;
	Gtk::HScale m_hsl_keyspeed;
	Gtk::HScale m_hsl_skill;

	Glib::RefPtr<Gnome::Conf::Client> m_conf_client;
	
	void on_btn_save_clicked();
	void on_txtchars_changed(const Glib::ustring&);
	bool on_configuration_changed(Gtk::ScrollType, double);
    };
}

#endif

