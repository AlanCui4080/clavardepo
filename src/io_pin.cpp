//     Copyright (C) 2023 AlanCui4080

//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU Affero General Public License as
//     published by the Free Software Foundation, either version 3 of the
//     License, or (at your option) any later version.

//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU Affero General Public License for more details.

//     You should have received a copy of the GNU Affero General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

/* SPDX-License-Identifier: AGPL-3.0-or-later */

#include <clava/io.hpp>

using namespace clava;
void io_pin::pull_up()
{
    this->group->set_pupd(this->id, io_pin::pupd::PU);
}
void io_pin::pull_down()
{
    this->group->set_pupd(this->id, io_pin::pupd::PD);
}
void io_pin::make_float()
{
    this->group->set_pupd(this->id, io_pin::pupd::NONE);
}
bool io_pin::read()
{
    return this->group->read(this->id);
}
void io_pin::write(bool val)
{
    this->group->write(this->id, val);
}
void io_pin::set()
{
    this->group->set(this->id);
}
void io_pin::reset()
{
    this->group->reset(this->id);
}
void io_pin::lock()
{
    this->group->lock(this->id);
}
