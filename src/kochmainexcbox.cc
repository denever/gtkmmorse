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
#include "kochmainexcbox.hh"
#include "resources.hh"

#include <gconfmm.h>

std::string charsets[] = {group_chars1, group_chars2, group_chars3, group_chars4, group_chars5, group_numbrs}; 

using namespace gtkmmorsegui;

KochMainExcBox::KochMainExcBox(Glib::RefPtr<Gnome::Conf::Client> conf_client):
    m_conf_client(conf_client),
    m_frm_stringlength(insert_strlen),
    m_frm_stringnum(insert_strnum),
    m_frm_charset(dlg_charset_title),
    m_btn_play("start"),
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

    append_charset(0, dlg_charset_choice1);
    append_charset(1, dlg_charset_choice2);
    append_charset(2, dlg_charset_choice3);
    append_charset(3, dlg_charset_choice4);
    append_charset(4, dlg_charset_choice5);
    append_charset(5, dlg_charset_choice6);

    m_ali_charset.set_padding(30,30,30,30);
    m_ali_charset.add(m_cmb_charset);
    m_frm_charset.add(m_ali_charset);
    
    m_hbb_buttons.pack_start(m_btn_play);
    
    m_box_main.pack_start(m_frm_stringlength, Gtk::PACK_SHRINK);
    m_box_main.pack_start(m_frm_stringnum, Gtk::PACK_SHRINK);
    m_box_main.pack_start(m_frm_charset, Gtk::PACK_SHRINK);
    m_box_main.pack_start(m_hbb_buttons);

    pack_start(m_box_main);
    pack_start(m_box_check);
    
    m_btn_play.signal_clicked().connect( sigc::mem_fun(*this, &KochMainExcBox::on_btn_play_clicked) );
    m_cmb_charset.signal_changed().connect( sigc::mem_fun(*this, &KochMainExcBox::on_cmb_charset_changed) );
    
    signal_exercise_started().connect( sigc::mem_fun(m_box_check, &CheckBox::on_exercise_started) );
    signal_exercise_finished().connect( sigc::mem_fun(m_box_check, &CheckBox::on_exercise_finished) );    
}

KochMainExcBox::~KochMainExcBox()
{}

sigc::signal<void, unsigned int, unsigned int, std::string>& KochMainExcBox::signal_exercise_started()
{
    return m_started;
}

sigc::signal<void, std::list<std::string> >& KochMainExcBox::signal_exercise_finished()
{
    return m_finished;
}

void KochMainExcBox::append_charset(unsigned int i, Glib::ustring charset)
{
    Gtk::TreeModel::Row row = *(m_ref_charset->append());
    row[m_mod_col.m_col_id] = i;
    row[m_mod_col.m_col_name] = charset;
}

void KochMainExcBox::on_cmb_charset_changed()
{
    m_btn_play.set_sensitive(true);
}

void KochMainExcBox::on_btn_play_clicked()
{
    m_btn_play.set_sensitive(false);
    
    Gtk::TreeModel::Row row = *m_cmb_charset.get_active();
    std::string m_charset = charsets[row[m_mod_col.m_col_id]];

    unsigned int begin_pause = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/beginpause");
    unsigned int pitch = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/pitch");
    unsigned int keyspeed = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/keyspeed");
    unsigned int charpause = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/charpause");
    unsigned int strpause = (unsigned int) m_conf_client->get_float("/apps/gtkmmorse/keyer/stringpause");
    
    unsigned int strnum = (unsigned int) m_hsl_stringnum.get_value();
    unsigned int strlen = (unsigned int) m_hsl_stringlength.get_value();

    m_started.emit(strnum, strlen, m_charset);

    m_audioout = new libaudiostream::oastream();

    m_audioout->play_finished().connect( sigc::mem_fun(*this, &KochMainExcBox::on_play_finished) );
    
    libkeyer::Keyer current_keyer(m_audioout, keyspeed, charpause, strpause, pitch);

    libexercises::Blocks blocks_exc(strnum, m_charset, strlen);

    m_exercise_strings = blocks_exc.stringtok();
    
    m_audioout->enqueue_pause(begin_pause*1000);
    
    current_keyer << blocks_exc;
    
    m_audioout->play();

    m_audioout->enqueue_pause(begin_pause*1000);
}

void KochMainExcBox::on_play_finished()
{
    delete m_audioout;
    m_btn_play.set_sensitive(true);
    m_finished.emit(m_exercise_strings);    
}
