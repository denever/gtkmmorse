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

#include "mainwindow.hh"
#include "resources.hh"

using namespace gtkmmorsegui;

MainWindow::MainWindow(Glib::RefPtr<Gnome::Conf::Client> conf_client):
    m_btn_quit("Quit"),
    m_box_koch(conf_client),
    m_box_setup(conf_client),
    m_box_block(conf_client),
    m_box_kochsetup(conf_client)
{
    set_title(mainwindow_title);
    set_border_width(10);
    set_default_size(800, 300);
    add(m_box_main);

    m_box_main.pack_start(m_box_left);
    m_box_main.pack_start(m_box_right);

    m_box_right.pack_start(m_nbkmain);
    m_box_right.pack_start(m_btn_quit, Gtk::PACK_SHRINK);
    
    m_box_left.pack_start(m_box_check);
    
    m_nbkmain.append_page(m_box_block, mainwindow_item1);    
    m_nbkmain.append_page(m_box_koch, mainwindow_item2);
    m_nbkmain.append_page(m_box_kochsetup, mainwindow_item6);
    m_nbkmain.append_page(m_box_setup, mainwindow_item5);    
    
    show_all_children();
    
    m_btn_quit.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_btn_quit_clicked) );

    m_box_block.signal_exercise_started().connect( sigc::mem_fun(m_box_check, &CheckBox::on_exercise_started) );
    m_box_block.signal_exercise_finished().connect( sigc::mem_fun(m_box_check, &CheckBox::on_exercise_finished) );    
}

MainWindow::~MainWindow()
{}

void MainWindow::on_btn_quit_clicked()
{
    hide();
}
