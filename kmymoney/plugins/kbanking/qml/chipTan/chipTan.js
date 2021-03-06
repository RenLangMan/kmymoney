/*
 * A tan input dialog for optical chipTan used in online banking
 * Copyright 2014  Christian David <c.david@christian-david.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * @brief Code to transmit
 * Array of int's each int is a half-byte, they are reorderd for transmission
 */
var transmitCode = []

/** @brief currently shown half-byte of transmitCode */
var currentIndex = 0
/**
 * @brief Indicates if first or second half of clock is displayed
 * First bar (showing clock) is on if this is true, off otherwise.
 */
var currentIntervalStarted = true

function timerStarted( data, parentItem )
{
  // Startcode
  transmitCode = [ 0x0, 0xF, 0xF ]

  // Set Code (half-bytes are switched)
  for (var i = 0; i < data.length; i+=2) {
      transmitCode.push(parseInt(data[i+1], 16))
      transmitCode.push(parseInt(data[i], 16))
  }
}

/**
 * @brief Shows next clock of transmitCode
 */
function timerTriggered( parentItem )
{
  if (currentIntervalStarted == true) {
      parentItem.children[0].bitState = false
      currentIntervalStarted = false;
      return
  }

  parentItem.children[0].bitState = true
  parentItem.children[1].bitState = transmitCode[currentIndex] & 1
  parentItem.children[2].bitState = transmitCode[currentIndex] & 2
  parentItem.children[3].bitState = transmitCode[currentIndex] & 4
  parentItem.children[4].bitState = transmitCode[currentIndex] & 8

  ++currentIndex
  currentIntervalStarted = true
  if (currentIndex >= transmitCode.length)
      currentIndex = 0
}
