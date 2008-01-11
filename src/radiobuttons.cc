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
  m_rbt_firstpattern("@"),
  m_rbt_seconpattern("*")
{
  Gtk::RadioButton::Group group = m_rbt_firstpattern.get_group();
  m_rbt_seconpattern.set_group(group);

  pack_start(m_rbt_firstpattern);
  pack_start(m_rbt_seconpattern);  
}

RadioButtons::~RadioButtons()
{
}
