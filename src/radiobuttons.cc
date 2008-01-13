//$Id: radiobuttons.cc 836 2007-05-09 03:02:38Z jjongsma $ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "radiobuttons.hh"

using namespace gtkmmorsegui;

RadioButtons::RadioButtons() :
    m_choice(0)
{
    pack_start(m_ckb_choice1, Gtk::PACK_SHRINK);
    pack_start(m_ckb_choice2, Gtk::PACK_SHRINK);
    m_ckb_choice1.signal_clicked().connect( sigc::mem_fun(*this, &RadioButtons::on_ckb_choice1) );
    m_ckb_choice2.signal_clicked().connect( sigc::mem_fun(*this, &RadioButtons::on_ckb_choice2) );
}

RadioButtons::~RadioButtons()
{
}

void RadioButtons::set_tooltips(Glib::ustring choice1, Glib::ustring choice2)
{
    m_ckb_choice1.set_tooltip_text(choice1);
    m_ckb_choice2.set_tooltip_text(choice2);    
}

void RadioButtons::on_ckb_choice1()
{
    m_choice = 1;
    set_sensitive(false);
}

void RadioButtons::on_ckb_choice2()
{
    m_choice = 2;
    set_sensitive(false);    
}

