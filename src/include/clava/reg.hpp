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

namespace clava
{
    /**
     * @brief keep refrence of a register
     * 
     * @tparam _Type the type of the register
     */
    template<typename _Type>
    class reg_base
    {
    private:
        _Type* base;
    public:
        using value_type = _Type;
        /**
         * @brief constructor
         * 
         * @param ptr the base of the register
         */
        reg_base(uintptr_t ptr)
        {
            base = reinterpret_cast<_Type*>(ptr);
        }
        /**
         * @brief get the base of the register
         * 
         * @return _Type& 
         */
        _Type* get_base()
        {
            return this->base;
        }
    };
    /**
     * @brief a writable register
     * 
     * @tparam _Type the type of the register
     */
    template<typename _Type>
    class w_reg : public reg_base<_Type>
    {
    public:
        using reg_base<_Type>::reg_base;
        /**
         * @brief write the register
         * 
         * @param val the value to be written in
         */
        void write(_Type val)
        {
            *this->get_base() = val;
        }
    };
    /**
     * @brief a readable register
     * 
     * @tparam _Type the type of the register
     */
    template<typename _Type>
    class r_reg :  public reg_base<_Type>
    {
    public:
        using reg_base<_Type>::reg_base;
        /**
         * @brief write the register
         * 
         * @param val the value to be written in
         */
        void write(_Type val)
        {
            *this->get_base() = val;
        }
        /**
         * @brief read the register
         * 
         * @return _Type
         */
        _Type read()
        {
            return *this->get_base();
        }
    };
    /**
     * @brief a both readable and writable register
     * 
     * @tparam _Type the type of the register
     */
    template<typename _Type>
    class rw_reg : public reg_base<_Type>
    {
    public:
        using reg_base<_Type>::reg_base;
        /**
         * @brief write the register
         * 
         * @param val the value to be written in
         */
        void write(_Type val)
        {
            *this->get_base() = val;
        }
        /**
         * @brief read the register
         * 
         * @return _Type
         */
        _Type read()
        {
            return *this->get_base();
        }
        /**
         * @brief overwrite only masked area with val
         * @note  read the original value, write the masked bits with val, and write it back
         * @param mask the write bitmask
         * @param val the value to write
         */
        void cover(_Type mask, _Type val)
        {
            auto tmp = this->read();
            tmp &= mask;
            tmp |= val;
            this->write(tmp);
        }
    };

} // namespace clava
