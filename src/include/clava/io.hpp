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

#pragma once

#include <cstdint>
#include <array>

#include <clava/reg.hpp>

namespace clava
{
    /**
     * @brief the number of pins in a group
     * 
     */
    constexpr auto pin_in_group = 16;
    /**
     * @brief the type to descript a pin
     * 
     */
    typedef uint16_t pin_t;
    

    class io_group;
    /**
     * @brief an I/O pin
     * 
     */
    class io_pin
    {
    private:
        io_group* group; // the refrence of the group which this pin belongs to
        pin_t id; // the sequence of this pin in its group
        friend class io_group; //give io_group access to "group"
    public:
        /**
         * @brief mode of I/O pins
         * 
         */
        enum mode : uint8_t
        {
            IN = 0b00,
            OUT = 0b01,
            AF = 0b10,
            IO = 0b11,
        };
        /**
         * @brief output speed of I/O pins
         * @note refer to the device datasheet for the frequency specifications and the power supply
         * and load conditions for each speed - RM0444 Rev.5 p. 242
         * @warning the FT_c GPIOs cannot be set to high speed - RM0444 Rev.5 p. 242
         */
        enum speed : uint8_t
        {
            LOWEST = 0b00,
            LOW = 0b01,
            HIGH = 0b10,
            HIGHEST = 0b11,
        };
        /**
         * @brief output type of I/O pins
         * 
         */
        enum otype : bool
        {
            PUSH_PULL = 0,
            OPEN_SINK = 1,
        };
        /**
         * @brief internal pull-up/pull-down of I/O pins
         * 
         */
        enum pupd : uint8_t
        {
            NONE = 0b00,
            PU = 0b01,
            PD = 0b10,
        };


        io_pin();

        /**
         * @brief internally pull the pin up
         * 
         */
        void pull_up();
        /**
         * @brief internally pull the pin down
         * 
         */
        void pull_down();
        /**
         * @brief leave the pin floating
         * 
         */
        void make_float();

        /**
         * @brief read the value on the pin
         * @return bool
         */
        bool read();
        /**
         * @brief write value to the pin
         * @param val the value to be written in
         */
        void write(bool val);

        /**
         * @brief set the pin to 1
         * 
         */
        void set();
        /**
         * @brief reset the pin to 0
         * 
         */
        void reset();

        /**
         * @brief lock the attributes of the pin
         * 
         */
        void lock();
    };
    /**
     * @brief hardware-specific I/O abstraction
     * 
     */
    class io_base
    {
    private:
        rw_reg<uint32_t> moder; // pin mode
        rw_reg<uint32_t> otyper; // output type
        rw_reg<uint32_t> speedr; // output speed
        rw_reg<uint32_t> pupdr; // internal pull-up/pull-down
        r_reg<uint16_t> idr; // input
        w_reg<uint16_t> odr; // output
        w_reg<uint16_t> bsr; // set
        rw_reg<uint32_t> lckr; // lock
        rw_reg<uint32_t> afrl; // alternative
        rw_reg<uint32_t> afrh; // alternative
        w_reg<uint16_t> brr; // reset
    public:
        io_base(uintptr_t base);
        /**
         * @brief set the mode of the pin
         * 
         * @param pin the sequence of the pin
         * @param val the mode to be written in
         */
        void set_mode(pin_t pin, enum io_pin::mode val);
        /**
         * @brief get the mode of the pin
         * 
         * @param pin the sequence of the pin
         * @return enum io_pin::mode 
         */
        enum io_pin::mode get_mode(pin_t pin);
        /**
         * @brief set the output type of the pin
         * 
         * @param pin the sequence of the pin
         * @param val the output type to be written in
         */
        void set_otype(pin_t pin, enum io_pin::otype val);
        /**
         * @brief get the output type of the pin
         * 
         * @param pin the sequence of the pin
         * @return enum io_pin::otype 
         */
        enum io_pin::otype get_otype(pin_t pin);
        /**
         * @brief set the speed of the pin
         * 
         * @param pin the sequence of the pin
         * @param val the speed to be written in
         */
        void set_speed(pin_t pin, enum io_pin::speed val);
        /**
         * @brief get the speed of the pin
         * 
         * @param pin the sequence of the pin
         * @return enum io_pin::speed 
         */
        enum io_pin::speed get_speed(pin_t pin);

        /**
         * @brief set the internally PU/PD
         * 
         * @param pin the sequence of the pin
         * @param val the PU/PD to be written in
         */
        void set_pupd(pin_t pin, enum io_pin::pupd val);
        /**
         * @brief get the internally PU/PD
         * 
         * @param pin the sequence of the pin
         * @return enum io_pin::pupd 
         */
        enum io_pin::pupd get_pupd(pin_t pin);
        /**
         * @brief set the pin to 1
         * 
         * @param pin the sequence of the pin
         */
        void set(pin_t pin);
        /**
         * @brief reset the pin to 0
         * 
         * @param pin the sequence of the pin
         */
        void reset(pin_t pin);
        /**
         * @brief lock the attributes of the pin
         * @warning When the LOCK sequence has been applied on a port bit, 
         * the value of this port bit can no longer be modified until 
         * the next MCU reset or peripheral reset. - RM0444 Rev.5 p. 244
         * @param pin the sequence of the pin
         */
        void lock(pin_t pin);
        /**
         * @brief lockdown all attributes
         * @warning When the LOCK sequence has been applied on a port bit, 
         * the value of this port bit can no longer be modified until 
         * the next MCU reset or peripheral reset. - RM0444 Rev.5 p. 244
         */
        void lockdown();
        /**
         * @brief read the value on the pin
         * 
         * @param pin the sequence of the pin
         * @return bool
         */
        bool read(pin_t pin);
        /**
         * @brief write value to the pin
         * 
         * @param pin the sequence of the pin
         * @param val the value to be written in
         */
        void write(pin_t pin, bool val);

    };
    /**
     * @brief fuction management I/O group
     * 
     */
    class io_group : public io_base
    {
    private:
        /**
         * @brief refrence to all the pins in the group
         * 
         */
        std::array<io_pin, pin_in_group> list;
    public:
        io_group(uintptr_t base);
        /**
         * @brief get a specific pin in the group
         * 
         * @param pin the sequence of the pin
         * @return io_pin& 
         */
        io_pin& operator[](pin_t pin);
    };
} // namespace clava
