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

#include "kochsetupbox.hh"
#include "resources.hh"

#include <gtkmm/entry.h>
#include <gconfmm.h>

using namespace gtkmmorsegui;

KochSetupBox::KochSetupBox(Glib::RefPtr<Gnome::Conf::Client> conf_client):
    m_frm_chars(insert_chars),
    m_frm_charitem(insert_pos),
    m_frm_stringnumbers(insert_strpause),
    m_frm_stringlength(insert_strlen),
    m_frm_keyspeed(insert_wpm),
    m_frm_skill(insert_skill),
    
    m_btn_save("Save configuration"),
    m_conf_client(conf_client)
{
    if( ! m_conf_client->dir_exists("/apps/gtkmmorse/koch") )
    {
	m_conf_client->add_dir("/apps/gtkmmorse");
	m_conf_client->add_dir("/apps/gtkmmorse/koch");

	Glib::ustring prova("ei");

	m_conf_client->set("/apps/gtkmmorse/koch/chars", prova );

	m_conf_client->set("/apps/gtkmmorse/koch/charitem", 2.0);
	m_conf_client->set("/apps/gtkmmorse/koch/stringnumbers",10.0 );
	m_conf_client->set("/apps/gtkmmorse/koch/stringlength", 3.0 );
	m_conf_client->set("/apps/gtkmmorse/koch/keyspeed", 10.0 );
	m_conf_client->set("/apps/gtkmmorse/koch/skill", 1.0);	    
    }
    
    m_txt_chars.set_text(m_conf_client->get_string("/apps/gtkmmorse/koch/chars"));

    Gtk::Adjustment adj_charitem(m_conf_client->get_float("/apps/gtkmmorse/koch/charitem"), 2.0, m_txt_chars.get_text().size());
    Gtk::Adjustment adj_stringnumbers(m_conf_client->get_float("/apps/gtkmmorse/koch/stringnumbers"), 1.0, 70.0);
    Gtk::Adjustment adj_stringlength(m_conf_client->get_float("/apps/gtkmmorse/koch/stringlength"), 1.0, 5.0);
    Gtk::Adjustment adj_keyspeed(m_conf_client->get_float("/apps/gtkmmorse/koch/keyspeed"), 1.0, 10.0);
    Gtk::Adjustment adj_skill(m_conf_client->get_float("/apps/gtkmmorse/koch/skill"), 500.0, 1000.0, 50.0);    

    m_hsl_keyspeed.set_adjustment(adj_keyspeed);
    m_hsl_charitem.set_adjustment(adj_charitem);
    m_hsl_stringnumbers.set_adjustment(adj_stringnumbers);
    m_hsl_stringlength.set_adjustment(adj_stringlength);
    m_hsl_skill.set_adjustment(adj_skill);

    m_hsl_keyspeed.set_update_policy(Gtk::UPDATE_CONTINUOUS);
    m_hsl_charitem.set_update_policy(Gtk::UPDATE_CONTINUOUS);
    m_hsl_stringnumbers.set_update_policy(Gtk::UPDATE_CONTINUOUS);
    m_hsl_stringlength.set_update_policy(Gtk::UPDATE_CONTINUOUS);
    m_hsl_skill.set_update_policy(Gtk::UPDATE_CONTINUOUS);

    m_hsl_keyspeed.set_digits(0);
    m_hsl_charitem.set_digits(0);
    m_hsl_stringnumbers.set_digits(0);
    m_hsl_stringlength.set_digits(0);
    m_hsl_skill.set_digits(0);

    m_hsl_keyspeed.set_draw_value();
    m_hsl_charitem.set_draw_value();
    m_hsl_stringnumbers.set_draw_value();
    m_hsl_stringlength.set_draw_value();
    m_hsl_skill.set_draw_value();


    m_frm_chars.add(m_txt_chars);
    m_frm_keyspeed.add(m_hsl_keyspeed);    
    m_frm_charitem.add(m_hsl_charitem);
    m_frm_stringnumbers.add(m_hsl_stringnumbers);
    m_frm_stringlength.add(m_hsl_stringlength);    
    m_frm_skill.add(m_hsl_skill);

    pack_start(m_frm_chars);
    pack_start(m_frm_keyspeed);
    pack_start(m_frm_charitem);
    pack_start(m_frm_stringnumbers);
    pack_start(m_frm_stringlength);
    pack_start(m_frm_skill);
    pack_start(m_btn_save, Gtk::PACK_SHRINK);

    m_btn_save.set_sensitive(false);
    m_btn_save.signal_clicked().connect( sigc::mem_fun(*this, &KochSetupBox::on_btn_save_clicked) );

    m_txt_chars.signal_insert_at_cursor().connect( sigc::mem_fun(*this, &KochSetupBox::on_txtchars_changed) );
    m_hsl_keyspeed.signal_change_value().connect( sigc::mem_fun(*this, &KochSetupBox::on_configuration_changed) );
    m_hsl_charitem.signal_change_value().connect( sigc::mem_fun(*this, &KochSetupBox::on_configuration_changed) );
    m_hsl_stringnumbers.signal_change_value().connect( sigc::mem_fun(*this, &KochSetupBox::on_configuration_changed) );
    m_hsl_stringlength.signal_change_value().connect( sigc::mem_fun(*this, &KochSetupBox::on_configuration_changed) );
    m_hsl_skill.signal_change_value().connect( sigc::mem_fun(*this, &KochSetupBox::on_configuration_changed) );        
}

KochSetupBox::~KochSetupBox()
{}

void KochSetupBox::on_txtchars_changed(const Glib::ustring& s)
{
    m_btn_save.set_sensitive(true);
}

bool KochSetupBox::on_configuration_changed(Gtk::ScrollType scroll, double value)
{
    m_btn_save.set_sensitive(true);
    return true;
}

void KochSetupBox::on_btn_save_clicked()
{
    m_conf_client->set("/apps/gtkmmorse/koch/chars", m_txt_chars.get_text() );
    m_conf_client->set("/apps/gtkmmorse/koch/keyspeed", m_hsl_keyspeed.get_value());
    m_conf_client->set("/apps/gtkmmorse/koch/charitem", m_hsl_charitem.get_value());
    m_conf_client->set("/apps/gtkmmorse/koch/stringnumbers", m_hsl_stringnumbers.get_value());
    m_conf_client->set("/apps/gtkmmorse/koch/stringlength", m_hsl_stringlength.get_value());
    m_conf_client->set("/apps/gtkmmorse/koch/skill", m_hsl_skill.get_value());
    
    m_btn_save.set_sensitive(false);
}
