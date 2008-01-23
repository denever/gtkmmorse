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

#ifndef BICHECKBUTTONS_HH
#define BICHECKBUTTONS_HH

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/separator.h>
#include <gtkmm/checkbutton.h>

namespace gtkmmorsegui
{
    class BiCheckButtons : public Gtk::VBox
    {
    public:
	BiCheckButtons();
	~BiCheckButtons();

	void set_tooltips(Glib::ustring, Glib::ustring);
	
	void on_ckb_choice1();
	void on_ckb_choice2();
	void set_ok();
	void set_no();
	void clear();
	
	inline int choice()
	{
	    return m_choice;
	}
	
    private:
	int m_choice;
	Gtk::Label m_lbl_ok;
	Gtk::Label m_lbl_no;
	Gtk::CheckButton m_ckb_choice1;
	Gtk::CheckButton m_ckb_choice2;
    };
}
#endif //RADIOBUTTONS_HH
