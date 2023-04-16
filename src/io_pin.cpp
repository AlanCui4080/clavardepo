/**
 * @file io_pin.cpp
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

#include <limits>

#include <clava/io.hpp>

using namespace clava;

io_pin::io_pin() : group(nullptr), id(std::numeric_limits<decltype(id)>::max()) {}

[[maybe_unused]] void io_pin::pull_up()
{
    this->group->set_pupd(this->id, io_attr::pupd_t::PU);
}

[[maybe_unused]] void io_pin::pull_down()
{
    this->group->set_pupd(this->id, io_attr::pupd_t::PD);
}

[[maybe_unused]] void io_pin::make_float()
{
    this->group->set_pupd(this->id, io_attr::pupd_t::NONE);
}

[[maybe_unused]] bool io_pin::read()
{
    return this->group->read(this->id);
}

[[maybe_unused]] void io_pin::write(bool val)
{
    this->group->write(this->id, val);
}

[[maybe_unused]] void io_pin::set()
{
    this->group->set(this->id);
}

[[maybe_unused]] void io_pin::reset()
{
    this->group->reset(this->id);
}

[[maybe_unused]] void io_pin::lock()
{
    this->group->lock(this->id);
}