// -*- C++ -*-
/***************************************************************************
    Copyright (C) 2007 Giuseppe "denever" Martino
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

#ifndef SKILL_H
#define SKILL_H

namespace libexercises
{
    const unsigned int chars1 = 0x01; // e,i,s,h,t,m,o
    const unsigned int chars2 = 0x02; // a,w,j,v,u
    const unsigned int chars3 = 0x04; // n,d,b,g
    const unsigned int chars4 = 0x08; // r,p,l,f
    const unsigned int chars5 = 0x10; // k,c,y,q,z,x
    const unsigned int numbrs = 0x20; // 0,1,2,3,4,5,6,7,8,9

    const unsigned int mixed  = 0x40; // totaly mixed
    const unsigned int submixed = 0x80; // group mixed

    const unsigned int skill1 = chars1 | mixed;
    const unsigned int skill2 = skill1 | chars2; // chars1 + chars2
    const unsigned int skill3 = skill2 | chars3; // skill2 + chars2
    const unsigned int skill4 = skill3 | chars4; // skill3 + chars3
    const unsigned int skill5 = skill4 | chars5; // skill4 + chars5
    const unsigned int skill6 = skill5 | numbrs; // skill5 + numbers
}

#endif // SKILL_H
