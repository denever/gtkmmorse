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
 ***************************************************************************/

#include "random.hh"
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;
using namespace librandom;

Random::Random()
{
    m_seed = time(0);
    m_count = time(0);
    srand(m_seed);
}

int Random::integer(int max)
{
  // Generate a random number between 0 and 1
  double normRand = double ( rand() ) / double ( RAND_MAX );

  // Make the possible range of numbers [0,max+1]. I'm adding one to max
  // because I'm going to use "floor" to convert from a double to an
  // integer.
  double rightRangeRand = (max + 1) * normRand;

  // Floor the double to get an integer. I'm using floor() because
  // rounding would lessen the chance of getting min or max as an output. By
  // adding one to max above and then flooring, each integer in the given
  // range has an equal chance of being selected.
  return ( int ( floor (rightRangeRand) ) );
}

int Random::integer(int min, int max)
{
  // Generate a random number between 0 and 1
  double normRand = double ( rand() ) / double ( RAND_MAX );

  // Make the possible range of numbers [0,max+1-min]. I'm adding one to max
  // because I'm going to use floor() to convert from a double to an
  // integer.
  double rightScaleRand = (max + 1 - min) * normRand;

  // Add min so that the random double will be in the range [min,max+1]
  double rightRangeRand = rightScaleRand + min;

  // Floor the double to get an integer. I'm using floor() because
  // rounding would lessen the chance of getting min or max as an output. By
  // adding one to max above and then flooring, each integer in the given
  // range has an equal chance of winning.
  return ( int ( floor (rightRangeRand) ) );
}

