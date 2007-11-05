// -*- C++ -*-
/***************************************************************************
                           GtkMMorse
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

#include "mainwindow.hh"

#include <gtkmm/main.h>
#include <gconfmm.h>

int main(int argc, char* argv[])
{
    Gnome::Conf::init();
    
    Glib::thread_init();

    Gtk::Main gtkmmorse(argc, argv);

    gtkmmorsegui::MainWindow window(Gnome::Conf::Client::get_default_client());

    Gtk::Main::run(window);
    
    return 0;
}
