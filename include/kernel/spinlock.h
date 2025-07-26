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

#ifndef __KERNEL_SPINLOCK_H
#define __KERNEL_SPINLOCK_H

#include <stdint.h>

struct spinlock {
	uint32_t lock;
};

#define KERNEL_SPINLOCK_INITIALIZER	{0}

void spinlock_lock(struct spinlock *spinlock);
void spinlock_unlock(struct spinlock *spinlock);

#endif /* __KERNEL_SPINLOCK_H */
