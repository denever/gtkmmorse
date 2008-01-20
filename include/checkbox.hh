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

#ifndef CHECKBOX_HH
#define CHECKBOX_HH

#include <gtkmm/box.h>
#include <gtkmm/scale.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/liststore.h>
#include <gtkmm/alignment.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/cellrendererprogress.h>

#include <string>
#include <list>

#include "keycheckentry.hh"

namespace gtkmmorsegui
{
    class ModelStringColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:
	
	ModelStringColumns()
	{
	    add(m_col_keyed);
	    add(m_col_copied);	    
	    add(m_col_percentage);
	}

	Gtk::TreeModelColumn<Glib::ustring> m_col_keyed;
	Gtk::TreeModelColumn<Glib::ustring> m_col_copied;	
	Gtk::TreeModelColumn<int> m_col_percentage;
    };

    class ModelSymbolColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:
	
	ModelSymbolColumns()
	{
	    add(m_col_symbol);
	    add(m_col_percentage);
	}

	Gtk::TreeModelColumn<Glib::ustring> m_col_symbol;
	Gtk::TreeModelColumn<int> m_col_percentage;
    };

    
    class CheckBox : public Gtk::VBox
    {
    public:
	CheckBox();
	~CheckBox();

	void on_exercise_started(unsigned int, unsigned int, std::string);
	void on_exercise_finished(std::list<std::string>);
	void on_txt_copied_return_pressed();

    private:
	unsigned short m_cols_count;
	unsigned int m_strings_lasted;
	unsigned int m_total_chars;
	std::string m_charset;
	
	KeyCheckEntry m_txt_copied;	

	Gtk::Frame m_frm_check;
	Gtk::Frame m_frm_legend;
	Gtk::Frame m_frm_overall;
	Gtk::Frame m_frm_smbrate;
	
	Gtk::Label m_lbl_legend;
	Gtk::TreeView m_trv_string;
	Gtk::TreeView m_trv_symbol;	
	Gtk::Alignment m_ali_check;
	Gtk::Alignment m_ali_overall;	
	Gtk::Alignment m_ali_smbrate;		
	Gtk::ScrolledWindow m_scl_string;
	Gtk::ScrolledWindow m_scl_symbol;	
	Gtk::CellRendererProgress* string_cell;
	Gtk::CellRendererProgress* symbol_cell;	

	Gtk::ProgressBar m_prb_overall;
	
	Glib::RefPtr<Gtk::ListStore> m_ref_string;
	Glib::RefPtr<Gtk::ListStore> m_ref_symbol;	
	
	ModelStringColumns m_mod_string;
	ModelSymbolColumns m_mod_symbol;	

	void append_copied(Glib::ustring);
	void append_symbol(char, unsigned int);	

	void prepare_scl_string();
	void prepare_scl_symbol();
    };
}

#endif
