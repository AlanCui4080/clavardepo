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

io_base::io_base(uintptr_t base): 
    moder(base  + 0x00),
    otyper(base + 0x04),
    speedr(base + 0x08),
    pupdr(base  + 0x0c),
    idr(base    + 0x10),
    odr(base    + 0x14),
    bsr(base    + 0x18),
    lckr(base   + 0x1c),
    afrl(base   + 0x20),
    afrh(base   + 0x24),
    brr(base    + 0x28)
{}

void io_base::set_mode(pin_t pin, io_attr::mode_t val)
{
    this->moder.cover(
        static_cast<decltype(lckr)::value_type>(0b11) << pin*2, 
        static_cast<decltype(lckr)::value_type>(val) << pin*2
        );
}
enum io_pin::mode io_base::get_mode(pin_t pin)
{
    return static_cast<enum io_pin::mode>((this->moder.read() >> pin*2) & 0b1);
}
void io_base::set_otype(pin_t pin, enum io_pin::otype val)
{
    this->otyper.cover(
        static_cast<decltype(lckr)::value_type>(0b1) << pin, 
        static_cast<decltype(lckr)::value_type>(val) << pin
        );
}
enum io_pin::otype io_base::get_otype(pin_t pin)
{
    return static_cast<enum io_pin::otype>((this->otyper.read() >> pin) & 0b11);
}
void io_base::set_speed(pin_t pin, enum io_pin::speed val)
{
    this->speedr.cover(
        static_cast<decltype(lckr)::value_type>(0b11) << pin*2, 
        static_cast<decltype(lckr)::value_type>(val) << pin*2
        );
}
enum io_pin::speed io_base::get_speed(pin_t pin)
{
    return static_cast<enum io_pin::speed>((this->speedr.read() >> pin*2) & 0b11);
}
void io_base::set_pupd(pin_t pin, enum io_pin::pupd val)
{
    this->pupdr.cover(
        static_cast<decltype(lckr)::value_type>(0b11) << pin*2, 
        static_cast<decltype(lckr)::value_type>(val) << pin*2
        );
}
enum io_pin::pupd io_base::get_pupd(pin_t pin)
{
    return static_cast<enum io_pin::pupd>((this->pupdr.read() >> pin*2) & 0b11);
}
void io_base::set(pin_t pin)
{
    this->bsr.write(static_cast<decltype(lckr)::value_type>(0b1) << pin);
}
void io_base::reset(pin_t pin)
{
    this->brr.write(static_cast<decltype(lckr)::value_type>(0b1) << pin);
}
void io_base::lock(pin_t pin)
{
    this->lckr.cover(
        (static_cast<decltype(lckr)::value_type>(0b1) << 16)
            | (static_cast<decltype(lckr)::value_type>(0b1) << pin), 
        (static_cast<decltype(lckr)::value_type>(0b1) << 16)
            | (static_cast<decltype(lckr)::value_type>(0b1) << pin)
        );
    this->lckr.cover(
        (static_cast<decltype(lckr)::value_type>(0b1) << 16)
            | (static_cast<decltype(lckr)::value_type>(0b1) << pin), 
        (static_cast<decltype(lckr)::value_type>(0b0) << 16)
            | (static_cast<decltype(lckr)::value_type>(0b1) << pin)
        );
    this->lckr.cover(
        (static_cast<decltype(lckr)::value_type>(0b1) << 16)
            | (static_cast<decltype(lckr)::value_type>(0b1) << pin), 
        (static_cast<decltype(lckr)::value_type>(0b1) << 16)
            | (static_cast<decltype(lckr)::value_type>(0b1) << pin)
        );
    
    this->lckr.read();
}
void io_base::lockdown()
{
    this->lckr.cover(
        (static_cast<decltype(lckr)::value_type>(0b1) << 16)|0xffff, 
        (static_cast<decltype(lckr)::value_type>(0b1) << 16)|0xffff
        );
    this->lckr.cover(
        (static_cast<decltype(lckr)::value_type>(0b1) << 16)|0xffff, 
        (static_cast<decltype(lckr)::value_type>(0b0) << 16)|0xffff
        );
    this->lckr.cover(
        (static_cast<decltype(lckr)::value_type>(0b1) << 16)|0xffff, 
        (static_cast<decltype(lckr)::value_type>(0b1) << 16)|0xffff
        );

    this->lckr.read();
}
bool io_base::read(pin_t pin)
{
    return (this->idr.read() >> pin) & 0b1;
}
void io_base::write(pin_t pin, bool val)
{
    this->odr.write(static_cast<decltype(lckr)::value_type>(val) << pin);
}
