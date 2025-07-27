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

#include <stdint.h>

/* Documentation:
 * https://blog.alex.balgavy.eu/a-practical-guide-to-gcc-inline-assembly/
 * https://wiki.osdev.org/Inline_Assembly/Examples
 * https://www.felixcloutier.com/x86/in
 * https://www.felixcloutier.com/x86/out
 * https://gcc.gnu.org/onlinedocs/gcc/Machine-Constraints.html#Machine-Constraints
 * https://stackoverflow.com/questions/32791997/gcc-inline-assembly-nd-constraint
 */

uint8_t inb(uint16_t port)
{
	uint8_t value;
	// by specifying "inb" as instruction there are two possible
	// options: IN AL, imm8 (where port is an 8-bit inmediate value)
	// and IN AL,DX, which takes the port value as the content of the
	// DX register. By setting "dN" as constraint of the port variable
	// we're telling the compiler it can choose whether to load the
	// value of port in DX and call IN AL,DX or (if port value fits in
	// 8-bits and is known at compile time) call IN AL,imm8 optimizing
	// out the load instruction
	__asm__ volatile ("inb %1, %0" : "=a" (value) : "dN" (port) : );
	return value;
}

void outb(uint16_t port, uint8_t value)
{
	__asm__ volatile ("outb %1, %0" : : "dN" (port), "a" (value) : );
}
