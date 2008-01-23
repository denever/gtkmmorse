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

#include "bicheckbuttons.hh"

using namespace gtkmmorsegui;

BiCheckButtons::BiCheckButtons() :
    m_choice(-1),
    m_lbl_ok("ok"),
    m_lbl_no("no")
{
    pack_start(m_ckb_choice1, Gtk::PACK_SHRINK);
    pack_start(m_ckb_choice2, Gtk::PACK_SHRINK);
    m_ckb_choice1.signal_clicked().connect( sigc::mem_fun(*this, &BiCheckButtons::on_ckb_choice1) );
    m_ckb_choice2.signal_clicked().connect( sigc::mem_fun(*this, &BiCheckButtons::on_ckb_choice2) );
}

BiCheckButtons::~BiCheckButtons()
{
}

void BiCheckButtons::set_tooltips(Glib::ustring choice1, Glib::ustring choice2)
{
    m_ckb_choice1.set_tooltip_text(choice1);
    m_ckb_choice2.set_tooltip_text(choice2);    
}

void BiCheckButtons::on_ckb_choice1()
{
    m_choice = 0;
    set_sensitive(false);
}

void BiCheckButtons::on_ckb_choice2()
{
    m_choice = 1;
    set_sensitive(false);    
}

void BiCheckButtons::set_ok()
{
    if(m_choice == 0)
    {
	m_ckb_choice1.add(m_lbl_ok);
	m_lbl_ok.show();
    }

    if(m_choice == 1)    
    {
	m_ckb_choice2.add(m_lbl_ok);
	m_lbl_ok.show();
    }
}

void BiCheckButtons::set_no()
{
    if(m_choice == 0)
    {
	m_ckb_choice1.add(m_lbl_no);
	m_lbl_no.show();
	m_ckb_choice1.set_inconsistent();	
    }

    if(m_choice == 1)
    {
	m_ckb_choice2.add(m_lbl_no);
	m_lbl_no.show();
	m_ckb_choice2.set_inconsistent();
    }
}

void BiCheckButtons::clear()
{
    m_ckb_choice1.remove();
    m_ckb_choice2.remove();

    m_lbl_ok.hide();
    m_lbl_no.hide();

    m_ckb_choice1.set_sensitive(true);
    m_ckb_choice2.set_sensitive(true);

    m_ckb_choice1.set_active(false);
    m_ckb_choice2.set_active(false);

    m_ckb_choice1.set_inconsistent(false);    
    m_ckb_choice2.set_inconsistent(false);

    set_sensitive(true);
    
    m_choice = -1;
}
