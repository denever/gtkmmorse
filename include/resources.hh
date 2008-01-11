// -*- C++ -*-
/***************************************************************************
                                 GtkMMorse
                          --------------------
    Copyright (C) 2007 Giuseppe "denever" Martino
    begin                : Sun May 6 2001
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

#ifdef HAVE_CONFIG_H
 #include "config.h"
#endif

#define chkmsg_legend "Please input the signs you copied.\nIf you didn't copy a sign, put @."

#define fbkmsg_title "EVALUATION"

#define ovrmsg_title "Overall success rate"
#define smbmsg_title "Success rate per symbol"
#define smbmsg_percentage "Percentage"
#define smbmsg_symbol "Symbol"
#define smbmsg_copiedok "copied correctly"
#define smbmsg_keyed "keyed"

#define cmpmsg_title "Comparison between keyed and copied sign groups"
#define cmpmsg_group "Group"
#define cmpmsg_mistakes "Mistakes - marked with"
#define cmpmsg_keyed "Keyed signs - what was transmitted"
#define cmpmsg_copied "Copied signs - what you have input"

#define mainwindow_title  "GtkMMorse " VERSION

#define mainwindow_item1  "Rhythm Exercise"
#define mainwindow_item2  "Pattern Exercise"
#define mainwindow_item3  "Main Exercise"
#define mainwindow_item4  "Setup"
#define mainwindow_item5  "Koch Setup"
#define mainwindow_item6  "Blocks method"

#define msg_start      "About to start keying. Get ready..."
#define msg_changes    "Change these settings from the Setup Menu."
#define msg_speed      "Keying speed: "
#define msg_strlen     "String length: "
#define msg_charset    "Training character set: "
#define msg_strnum     "Number of strings: "
#define msg_callformat "Template callsign: "

#define dlg_charset_title   "Select training character set"
#define dlg_charset_choice1 "e,i,s,h,t,m,o"
#define dlg_charset_choice2 "e,i,s,h,t,m,o,a,w,j,u,v"
#define dlg_charset_choice3 "e,i,s,h,t,m,o,a,w,j,u,v,n,d,b,g"
#define dlg_charset_choice4 "e,i,s,h,t,m,o,a,w,j,u,v,n,d,b,g,r,p,l,f"
#define dlg_charset_choice5 "e,i,s,h,t,m,o,a,w,j,u,v,n,d,b,g,r,p,l,f,k,c,y,q,z,x"
#define dlg_charset_choice6 "All chars and numbers"
#define dlg_charset_choice7 "Custom character set"

#define dlg_charset2_title    "Add a group or option to your exercise:"
#define dlg_charset2_choice1  "e,i,s,h,t,m,o"
#define dlg_charset2_choice2  "a,w,j,v,u"
#define dlg_charset2_choice3  "n,d,b,g"
#define dlg_charset2_choice4  "r,p,l,f"
#define dlg_charset2_choice5  "k,c,y,q,z,x"
#define dlg_charset2_choice6  "0123456789"
#define dlg_charset2_choice7  "Chars ordered "
#define dlg_charset2_choice8  "Chars submixed with group order"
#define dlg_charset2_choice9  "Chars mixed without group order "
#define dlg_charset2_choice10 "End"

#define dlg_koch_title    "Do you want to continue with the Koch method?"
#define dlg_koch_msg_start "Ready for start a Koch exercise"
#define dlg_koch_msg_success "Your overall success rate is %1. If you want you can go to the next level of koch exercise."
#define dlg_koch_msg_faliure     "Your overall success rate is %1. To go to next level of koch exercise you need at least an overall success of 90%.\
 Repeat previous exercise or stop koch exercise?"

#define dlg_koch_continue "Yes"
#define dlg_koch_exit     "No"

#define insert_device     "Soundcard device file"
#define insert_samplerate "Sample rate"
#define insert_samplesize "Sample size"

#define insert_beginpause "Pause before keying (seconds)"
#define insert_charpause  "Dots between two characters in a word"
#define insert_strpause   "Dots between two words"
#define insert_dotlen     "Dit length"
#define insert_linelen    "Dah length"
#define insert_pitch       "Frequency of buzzer (Hz)"

#define insert_chars      "Training character set"
#define insert_pos        "Starting position"    
#define insert_wpm        "Keying speed (words per minute)"
#define insert_strlen     "Length of strings"
#define insert_filename   "Name of file to read"
#define insert_strnum     "Number of strings to send"
#define insert_callformat "Enter callsign template"
#define insert_skill      "insert_skill"
#define conf_menu_title "Setup Menu"
#define conf_menu_item1 "Keyer Setup"
#define conf_menu_item2 "Blocks method Setup"
#define conf_menu_item3 "Koch method Setup"
#define conf_menu_item4 "Qrz exercise Setup"
#define conf_menu_item5 "Default Settings"
#define conf_menu_item6 "Return to Main Menu"


#define errmsg_noformat   "Configuration file is incorrectly formatted"
#define errmsg_overwrite  "You have tried to overwrite the configuration file"
#define errmsg_nooption   "Can't find an option in the configuration file"
#define errmsg_nosection  "Can't find section in the configuration file"
#define errmsg_noopenfile "Can't open the configuration file"
#define errmsg_nofile     "The configuration file doesn't exist"
#define errmsg_conf       "Select Default Settings in the Setup Menu"
#define errmsg_devicefile "Can't write on device file "
#define errmsg_rate       "Wrong rate"
#define errmsg_format     "Format error"
#define errmsg_fragment   "Fragment error"
#define errmsg_stereo     "Stereo error"

#define rhythmexc_explanation "This first exercise is to teach the student to hear and begin to become accustumed to hearing the different overall rhythms of sound and silence. Five letter random groups are going to be sent. At first these will all be unknown letters. As you hear each acoustic pattern of a letter in a five-letter group, you have to check the checkbutton in the place which corresponds to the position of that sound pattern within its group."

#define patternexc_explanation "This second exercise is to start to recognize the differences in rhythm-pattern between two quite different-sounding letters, and become familiar with the sound pattern of each character. This begins by introducing the two first character just as sound patterns. At this time they are not yet to be identified with their printed letters but with two symbol. @ for patter one and # for pattern two. You have to put @ and # in the place which corresponds respectively pattern one and pattern two."


