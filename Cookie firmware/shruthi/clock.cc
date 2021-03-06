// Copyright 2011 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// Global clock.

#include "shruthi/clock.h"

#include "shruthi/resources.h"

namespace shruthi {

Clock clock;

/* static */
uint16_t Clock::bpm_;

/* static */
uint32_t Clock::phase_;

/* static */
uint32_t Clock::phase_increment_;

/* static */
void Clock::Update(uint8_t bpm) {
  phase_increment_ = pgm_read_dword(lut_res_tempo_phase_increment + bpm - 40);
}

}  // namespace shruthi
