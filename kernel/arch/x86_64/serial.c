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

#include <kernel/arch/x86_64/ports.h>
#include <kernel/spinlock.h>

/*
 * This serial is initialized early on by the kernel in order to provide
 * a way for logging the start-up process right from the beginning.
 * Documentation:
 * https://wiki.osdev.org/Serial_Ports
 */

static struct spinlock serial_lock = KERNEL_SPINLOCK_INITIALIZER;

// must be called with lock held
static int serial_can_transmit()
{
	return inb(SERIAL_PORT + 5) & 0x20;
}

// must be called with lock held
static void serial_send_byte(char byte)
{
	while (!serial_can_transmit());

	outb(SERIAL_PORT, byte);
}

int serial_init()
{
	outb(SERIAL_PORT + 1, 0x00);    // Disable all interrupts
	outb(SERIAL_PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	outb(SERIAL_PORT + 0, 0x01);    // Set divisor to 3 (low byte) 115200 baud
	                                // (QEMU serial port default baudrate)
	outb(SERIAL_PORT + 1, 0x00);    //                  (high byte)
	outb(SERIAL_PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
	outb(SERIAL_PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outb(SERIAL_PORT + 4, 0x03);    // IRQs disabled, RTS/DSR set
	outb(SERIAL_PORT + 4, 0x16);    // Set in loopback mode, test the serial chip
	outb(SERIAL_PORT + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

	// Check if serial is faulty (i.e: not same byte as sent)
	if(inb(SERIAL_PORT + 0) != 0xAE) {
		return 1;
	}

	// If serial is not faulty set it in normal operation mode
	// (not-loopback with IRQs disabled and OUT#1 and OUT#2 bits enabled)
	outb(SERIAL_PORT + 4, 0x07);
	return 0;
}

void serial_send(char *s)
{
	// Serialize access to serial port (for SMP)
	spinlock_lock(&serial_lock);
	while (*s)
	{
		serial_send_byte(*s);
		s++;
	}
	serial_send_byte('\n');
	spinlock_unlock(&serial_lock);
}
