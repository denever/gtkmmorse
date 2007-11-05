// -*- C++ -*-
/***************************************************************************
                           GtkMMorse gui
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

#include "checkbox.hh"
#include "resources.hh"

using namespace gtkmmorsegui;

/*
 * This function compares two strings and returns lets the user input the copied sign groups
 */
unsigned int count_wrong_letters(Glib::ustring keyed, Glib::ustring copied)
{
    unsigned int wrong_letters = 0;

    Glib::ustring::const_iterator kit = keyed.begin();
    Glib::ustring::const_iterator cit = copied.begin();
    Glib::ustring::const_iterator kitend = keyed.end();
    Glib::ustring::const_iterator citend = copied.end();    

    while(kit != kitend)
	if(cit != citend)
	{
	    if(*kit != *cit)
		wrong_letters++;

	    ++kit;
	    ++cit;		
	}
	else
	{
	    wrong_letters++;
	    ++kit;
	}

    //wrong_letters = keyed.size(); // if copied key has a different lenght of keyed all letters are wrong

    return wrong_letters;
}

CheckBox::CheckBox():
    m_cols_count(0),
    m_strings_lasted(0),
    m_frm_check(cmpmsg_title),
    m_frm_legend("Legend"),
    m_frm_overall(ovrmsg_title),
    m_frm_smbrate(smbmsg_title),
    m_lbl_legend(chkmsg_legend)
{
    m_txt_copied.set_sensitive(false);

    prepare_scl_string();
    prepare_scl_symbol();    
    
    m_ali_check.add(m_scl_string);
    m_ali_check.set_padding(0,5,8,8);
    m_frm_check.add(m_ali_check);
    pack_start(m_frm_check);
    
    m_ali_smbrate.set_padding(0,5,8,8);
    m_ali_smbrate.add(m_scl_symbol);
    m_frm_smbrate.add(m_ali_smbrate);    
    pack_start(m_frm_smbrate);

    m_ali_overall.set_padding(20,20,10,10);
    m_ali_overall.add(m_prb_overall);
    m_frm_overall.add(m_ali_overall);    
    pack_start(m_frm_overall);
    
    m_frm_legend.add(m_lbl_legend);
    pack_start(m_frm_legend);

    pack_start(m_txt_copied, Gtk::PACK_SHRINK);

    m_txt_copied.signal_return_pressed().connect( sigc::mem_fun(*this, &CheckBox::on_txt_copied_return_pressed) );
//    m_btn_check.signal_clicked().connect( sigc::mem_fun(*this, &CheckBox::on_btn_check_clicked) );
}

CheckBox::~CheckBox()
{}

void CheckBox::append_copied(Glib::ustring copied)
{
  Gtk::TreeModel::Row row = *(m_ref_string->append());
  row[m_mod_string.m_col_copied] = copied;
}

void CheckBox::on_txt_copied_return_pressed()
{
    if(m_strings_lasted > 0)
    {
	append_copied(m_txt_copied.get_text());
	m_strings_lasted--;
    }
    m_txt_copied.set_text("");
}

void CheckBox::on_exercise_started(unsigned int num_strings)
{
    m_strings_lasted = num_strings;
    m_txt_copied.set_sensitive(true);
    m_txt_copied.grab_focus();
    m_ref_string->clear();
}

void CheckBox::on_exercise_finished(std::list<std::string> lst)
{
    m_txt_copied.set_sensitive(false);
    
    std::list<std::string>::const_iterator cit = lst.begin();

    typedef Gtk::TreeModel::Children type_children; //minimise code length.
    type_children children = m_ref_string->children();
    for(type_children::iterator iter = children.begin(); iter != children.end(); ++iter)
    {
	Gtk::TreeModel::Row row = *iter;
	Glib::ustring temp = row[m_mod_string.m_col_copied];
	row[m_mod_string.m_col_keyed] = *cit;
	double percentage = double(count_wrong_letters(row[m_mod_string.m_col_keyed], row[m_mod_string.m_col_copied])) / double(cit->size());
	row[m_mod_string.m_col_percentage] = 100 - int(100*percentage);
	cit++;
    }
}

/*
  void CheckBox::append_result(Glib::ustring keyed, Glib::ustring copied, unsigned int percentage)
{
  Gtk::TreeModel::Row row = *(m_ref_string->append());
  row[m_mod_string.m_col_keyed] = keyed;
  row[m_mod_string.m_col_copied] = copied;
  row[m_mod_string.m_col_percentage] = percentage;
}
*/

void CheckBox::prepare_scl_string()
{
    m_scl_string.add(m_trv_string);
    m_scl_string.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    m_ref_string = Gtk::ListStore::create(m_mod_string);
    m_trv_string.set_model(m_ref_string);

    m_cols_count = m_trv_string.append_column("Copied", m_mod_string.m_col_copied);
    m_cols_count = m_trv_string.append_column("Keyed", m_mod_string.m_col_keyed);
    
    string_cell = new Gtk::CellRendererProgress;
    m_cols_count = m_trv_string.append_column("Percentage", *string_cell);

    Gtk::TreeViewColumn* pColumn = m_trv_string.get_column(m_cols_count - 1);
  
    if(pColumn)
    {
#ifdef GLIBMM_PROPERTIES_ENABLED
	pColumn->add_attribute(string_cell->property_value(), m_mod_string.m_col_percentage);
#else
	pColumn->add_attribute(*string_cell, "value", m_mod_string.m_col_percentage);
#endif
    }
}

void CheckBox::prepare_scl_symbol()
{
    m_scl_symbol.add(m_trv_symbol);
    m_scl_symbol.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    m_ref_symbol = Gtk::ListStore::create(m_mod_symbol);
    m_trv_symbol.set_model(m_ref_symbol);

    m_cols_count = m_trv_symbol.append_column(smbmsg_symbol, m_mod_symbol.m_col_symbol);

    symbol_cell = new Gtk::CellRendererProgress;

    m_cols_count = m_trv_symbol.append_column(smbmsg_percentage, *symbol_cell);

    Gtk::TreeViewColumn* pColumn = m_trv_symbol.get_column(m_cols_count - 1);
  
    if(pColumn)
    {
#ifdef GLIBMM_PROPERTIES_ENABLED
	pColumn->add_attribute(symbol_cell->property_value(), m_mod_symbol.m_col_percentage);
#else
	pColumn->add_attribute(*symbol_cell, "value", m_mod_symbol.m_col_percentage);
#endif
    }
}
