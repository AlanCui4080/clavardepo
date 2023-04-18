/**
 * @file io_group.cpp
 *
 * @attention
 * <h2> Copyright (C) 2023 clavardepo authors </h2>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/* SPDX-License-Identifier: AGPL-3.0-or-later */

#include <algorithm>

#include <clava/io.hpp>

using namespace clava;

io_pin& io_group::operator[](pin_t pin)
{
    return list[pin];
}

[[maybe_unused]] io_group::io_group(uintptr_t base)
    : io_base(base)
{
    for (auto& it : list) {
        it.group = this;
    }
}
