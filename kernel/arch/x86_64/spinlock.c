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

#include <kernel/spinlock.h>
#include <stdbool.h>

/*
 * Documentation:
 * https://wiki.osdev.org/Spinlock
 * https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html
 * https://wiki.osdev.org/Atomic_operation
 * https://stackoverflow.com/a/36685056
 */

void spinlock_lock(struct spinlock *spinlock)
{
	uint32_t expected_state = 0;
	uint32_t desired_state = 1;
	while (!__atomic_compare_exchange_n(&spinlock->lock, &expected_state, desired_state, false,
		__ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST))
		;
}

void spinlock_unlock(struct spinlock *spinlock)
{
	__atomic_store_n(&spinlock->lock, 0, __ATOMIC_SEQ_CST);
}
