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

#include "blocks.hh"
#include "blockbox.hh"
#include "resources.hh"

#include <gconfmm.h>

using namespace gtkmmorsegui;

BlockBox::BlockBox(Glib::RefPtr<Gnome::Conf::Client> conf_client):
    m_conf_client(conf_client),
    m_charset(0),
    m_frm_stringlength(insert_strlen),
    m_frm_stringnum(insert_strnum),
    m_frm_charset(dlg_charset_title),
    m_btn_play("start"),
    m_btn_submixed(dlg_charset2_choice8),
    m_adj_stringlength(5.0, 1.0, 20.0),
    m_adj_stringnum(3.0, 1.0, 70.0)
{
    m_btn_play.set_sensitive(false);
    
    m_ref_charset = Gtk::ListStore::create(m_mod_col);
    m_cmb_charset.set_model(m_ref_charset);
    m_cmb_charset.pack_start(m_mod_col.m_col_name); 

    m_hsl_stringlength.set_adjustment(m_adj_stringlength);
    m_hsl_stringnum.set_adjustment(m_adj_stringnum);

    m_hsl_stringlength.set_update_policy(Gtk::UPDATE_CONTINUOUS);
    m_hsl_stringnum.set_update_policy(Gtk::UPDATE_CONTINUOUS);

    m_hsl_stringlength.set_digits(0);
    m_hsl_stringnum.set_digits(0);

    m_hsl_stringlength.set_draw_value();
    m_hsl_stringnum.set_draw_value();
    
    m_frm_stringlength.add(m_hsl_stringlength);
    m_frm_stringnum.add(m_hsl_stringnum);

    append_charset(libexercises::skill1, dlg_charset_choice1);
    append_charset(libexercises::skill2, dlg_charset_choice2);
    append_charset(libexercises::skill3, dlg_charset_choice3);
    append_charset(libexercises::skill4, dlg_charset_choice4);
    append_charset(libexercises::skill5, dlg_charset_choice5);
    append_charset(libexercises::skill6, dlg_charset_choice6);

    m_ali_charset.set_padding(70,70,70,70);
    m_ali_charset.add(m_cmb_charset);
    m_frm_charset.add(m_ali_charset);
    
    m_hbb_buttons.pack_start(m_btn_submixed);
    m_hbb_buttons.pack_start(m_btn_play);
    
    pack_start(m_frm_stringlength);    
    pack_start(m_frm_stringnum);
    pack_start(m_frm_charset);
    pack_start(m_hbb_buttons);
    
    m_btn_play.signal_clicked().connect( sigc::mem_fun(*this, &BlockBox::on_btn_play_clicked) );
    m_cmb_charset.signal_changed().connect( sigc::mem_fun(*this, &BlockBox::on_cmb_charset_changed) );
}

BlockBox::~BlockBox()
{}

sigc::signal<void, unsigned int>& BlockBox::signal_exercise_started()
{
    return m_started;
}

sigc::signal<void, std::list<std::string> >& BlockBox::signal_exercise_finished()
{
    return m_finished;
}

void BlockBox::append_charset(unsigned int i, Glib::ustring charset)
{
    Gtk::TreeModel::Row row = *(m_ref_charset->append());
    row[m_mod_col.m_col_id] = i;
    row[m_mod_col.m_col_name] = charset;
}

void BlockBox::on_cmb_charset_changed()
{
    m_btn_play.set_sensitive(true);
}

void BlockBox::on_btn_play_clicked()
{
    m_btn_play.set_sensitive(false);
    
    Gtk::TreeModel::Row row = *m_cmb_charset.get_active();
    m_charset = row[m_mod_col.m_col_id];
    
    if(m_btn_submixed.get_active())
	m_charset |= libexercises::submixed;

    unsigned int begin_pause = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/beginpause");
    unsigned int tone = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/tone");
    unsigned int keyspeed = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/keyspeed");
    unsigned int charpause = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/charpause");
    unsigned int strpause = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/strpause");
    unsigned int linelen = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/linelen");    

    unsigned int strnum = (unsigned int) m_hsl_stringnum.get_value();
    unsigned int strlen = (unsigned int) m_hsl_stringlength.get_value();

    m_started.emit(strnum);

    m_audioout = new libaudiostream::oastream();

    m_audioout->play_finished().connect( sigc::mem_fun(*this, &BlockBox::on_play_finished) );
    
    libkeyer::Keyer current_keyer(m_audioout, keyspeed, charpause, strpause, 1, linelen);

    current_keyer.set_tone(tone);

    libexercises::Blocks blocks_exc(strnum, m_charset, strlen);

    m_exercise_strings = blocks_exc.stringtok();
    
    m_audioout->enqueue_pause(begin_pause*1000);
    
    current_keyer<<blocks_exc;
    
    m_audioout->play();

    m_audioout->enqueue_pause(begin_pause*1000);
}

void BlockBox::on_play_finished()
{
    delete m_audioout;
    m_btn_play.set_sensitive(true);
    m_finished.emit(m_exercise_strings);    
}
