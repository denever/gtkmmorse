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

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "kochbox.hh"
#include "blockbox.hh"
#include "setupbox.hh"
#include "checkbox.hh"
#include "kochsetupbox.hh"

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/notebook.h>

#include <gconfmm.h>

namespace gtkmmorsegui
{
    class MainWindow : public Gtk::Window
    {
    public:
	MainWindow(Glib::RefPtr<Gnome::Conf::Client> conf_client);
	~MainWindow();

    private:
	Gtk::Button m_btn_quit;
	
	Gtk::HBox m_box_main;
	Gtk::VBox m_box_left;
	Gtk::VBox m_box_right;	

	Gtk::Notebook m_nbkmain;

	gtkmmorsegui::KochBox m_box_koch;
	gtkmmorsegui::SetupBox m_box_setup;
	gtkmmorsegui::BlockBox m_box_block;
	gtkmmorsegui::CheckBox m_box_check;
	gtkmmorsegui::KochSetupBox m_box_kochsetup;
	
	void on_btn_quit_clicked();
    };
}

#endif

