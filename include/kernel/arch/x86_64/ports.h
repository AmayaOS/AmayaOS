/*
 * Copyright (C) 2025 Daniel Martín
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __KERNEL_ARCH_X86_64_PORTS_H
#define __KERNEL_ARCH_X86_64_PORTS_H

#include <stdint.h>

#define SERIAL_PORT 0x3f8 // COM1

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t value);

#endif /* __KERNEL_ARCH_X86_64_PORTS_H */
