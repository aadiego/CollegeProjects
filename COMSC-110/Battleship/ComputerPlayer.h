/* Aric Adiego
   Huda Biltagi
   COMSC-110, Section 8001 (Introduction to Programming) Final Project
   Instructor: Michael Wallace
   2018-12-13

   ------------------------------------------------------------------------------
   MIT License
   ------------------------------------------------------------------------------
   Copyright (c) 2018 Aric Adiego and Huda Biltagi

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#ifndef ComputerPlayer_H
#define ComputerPlayer_H
#include <string>
using namespace std;

// ------------------------------------------------------------------------------
// enum Mode
// IDLE (0)        Next attack location will be randomly selected.
// HUNTING (1)     A previous attack successfully hit a player's ship. Next
//                 attack location will be on one of the cardinal directions.
// ATTACKING (2)   The previous attacks have successfully hit a player's ship.
//                 The next attack location will be in the same direction until
//                 a) the ship is reported as sunk, or b) there is a reported
//                 miss which will start from the other end of the first
//                 successful attack coordinate.
// ------------------------------------------------------------------------------
enum Mode { IDLE, HUNTING, ATTACKING };
enum Direction { UP, LEFT, DOWN, RIGHT };

string SimpleAI_SelectTarget();
void SelectDirection();
void ProcessAttackStatus(int, int, int);

#endif