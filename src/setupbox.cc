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

#include "setupbox.hh"
#include "resources.hh"

#include <gconfmm.h>

using namespace gtkmmorsegui;

SetupBox::SetupBox(Glib::RefPtr<Gnome::Conf::Client> conf_client):
    m_frm_beginpause(insert_beginpause),
    m_frm_keyspeed(insert_wpm),
    m_frm_charpause(insert_charpause),
    m_frm_stringpause(insert_strpause),
    m_frm_tone(insert_tone),
    m_frm_linelen(insert_linelen),

    m_btn_save("Save configuration"),
    m_conf_client(conf_client)
{
    if( ! m_conf_client->dir_exists("/apps/gtkmmorse/keyer") )
    {
	    m_conf_client->add_dir("/apps/gtkmmorse");
	    m_conf_client->add_dir("/apps/gtkmmorse/keyer");

	    m_conf_client->set("/apps/gtkmmorse/keyer/beginpause", 2.0 );
	    m_conf_client->set("/apps/gtkmmorse/keyer/keyspeed",10.0 );
	    m_conf_client->set("/apps/gtkmmorse/keyer/charpause", 3.0 );
	    m_conf_client->set("/apps/gtkmmorse/keyer/stringpause", 7.0 );
	    m_conf_client->set("/apps/gtkmmorse/keyer/tone", 900.0);
	    m_conf_client->set("/apps/gtkmmorse/keyer/linelen", 3.0);
    }
    
    Gtk::Adjustment adj_beginpause(m_conf_client->get_float("/apps/gtkmmorse/keyer/beginpause"), 1.0, 6.0);
    Gtk::Adjustment adj_keyspeed(m_conf_client->get_float("/apps/gtkmmorse/keyer/keyspeed"), 10.0, 70.0);
    Gtk::Adjustment adj_charpause(m_conf_client->get_float("/apps/gtkmmorse/keyer/charpause"), 1.0, 5.0);
    Gtk::Adjustment adj_stringpause(m_conf_client->get_float("/apps/gtkmmorse/keyer/stringpause"), 1.0, 10.0);
    Gtk::Adjustment adj_tone(m_conf_client->get_float("/apps/gtkmmorse/keyer/tone"), 500.0, 1000.0, 50.0);
    Gtk::Adjustment adj_linelen(m_conf_client->get_float("/apps/gtkmmorse/keyer/linelen"), 3.0, 7.0);
    
    m_hsl_beginpause.set_adjustment(adj_beginpause);
    m_hsl_keyspeed.set_adjustment(adj_keyspeed);
    m_hsl_charpause.set_adjustment(adj_charpause);
    m_hsl_stringpause.set_adjustment(adj_stringpause);
    m_hsl_tone.set_adjustment(adj_tone);
    m_hsl_linelen.set_adjustment(adj_linelen);
    
    m_hsl_beginpause.set_update_policy(Gtk::UPDATE_CONTINUOUS);
    m_hsl_keyspeed.set_update_policy(Gtk::UPDATE_CONTINUOUS);
    m_hsl_charpause.set_update_policy(Gtk::UPDATE_CONTINUOUS);
    m_hsl_stringpause.set_update_policy(Gtk::UPDATE_CONTINUOUS);
    m_hsl_tone.set_update_policy(Gtk::UPDATE_CONTINUOUS);
    m_hsl_linelen.set_update_policy(Gtk::UPDATE_CONTINUOUS);

    m_hsl_beginpause.set_digits(0);
    m_hsl_keyspeed.set_digits(0);
    m_hsl_charpause.set_digits(0);
    m_hsl_stringpause.set_digits(0);
    m_hsl_tone.set_digits(0);
    m_hsl_linelen.set_digits(0);

    m_hsl_beginpause.set_draw_value();
    m_hsl_keyspeed.set_draw_value();
    m_hsl_charpause.set_draw_value();
    m_hsl_stringpause.set_draw_value();
    m_hsl_tone.set_draw_value();
    m_hsl_linelen.set_draw_value();

    m_frm_beginpause.add(m_hsl_beginpause);    
    m_frm_keyspeed.add(m_hsl_keyspeed);    
    m_frm_charpause.add(m_hsl_charpause);
    m_frm_stringpause.add(m_hsl_stringpause);    
    m_frm_tone.add(m_hsl_tone);
    m_frm_linelen.add(m_hsl_linelen);    

    pack_start(m_frm_beginpause);
    pack_start(m_frm_keyspeed);
    pack_start(m_frm_charpause);
    pack_start(m_frm_stringpause);
    pack_start(m_frm_tone);
    pack_start(m_frm_linelen);
    pack_start(m_btn_save, Gtk::PACK_SHRINK);

    m_btn_save.set_sensitive(false);
    m_btn_save.signal_clicked().connect( sigc::mem_fun(*this, &SetupBox::on_btn_save_clicked) );

    m_hsl_beginpause.signal_change_value().connect( sigc::mem_fun(*this, &SetupBox::on_configuration_changed) );
    m_hsl_keyspeed.signal_change_value().connect( sigc::mem_fun(*this, &SetupBox::on_configuration_changed) );
    m_hsl_charpause.signal_change_value().connect( sigc::mem_fun(*this, &SetupBox::on_configuration_changed) );
    m_hsl_stringpause.signal_change_value().connect( sigc::mem_fun(*this, &SetupBox::on_configuration_changed) );
    m_hsl_tone.signal_change_value().connect( sigc::mem_fun(*this, &SetupBox::on_configuration_changed) );
    m_hsl_linelen.signal_change_value().connect( sigc::mem_fun(*this, &SetupBox::on_configuration_changed) );        
}

SetupBox::~SetupBox()
{}

bool SetupBox::on_configuration_changed(Gtk::ScrollType scroll, double value)
{
    m_btn_save.set_sensitive(true);
    return true;
}

void SetupBox::on_btn_save_clicked()
{
    m_conf_client->set("/apps/gtkmmorse/keyer/beginpause", m_hsl_beginpause.get_value() );
    m_conf_client->set("/apps/gtkmmorse/keyer/keyspeed", m_hsl_keyspeed.get_value());
    m_conf_client->set("/apps/gtkmmorse/keyer/charpause", m_hsl_charpause.get_value());
    m_conf_client->set("/apps/gtkmmorse/keyer/stringpause", m_hsl_stringpause.get_value());
    m_conf_client->set("/apps/gtkmmorse/keyer/tone", m_hsl_tone.get_value());
    m_conf_client->set("/apps/gtkmmorse/keyer/linelen", m_hsl_linelen.get_value());
    
    m_btn_save.set_sensitive(false);
}
