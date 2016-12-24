#ifndef _INL_UTILITY_BITFIELD_
#define _INL_UTILITY_BITFIELD_

#include "Utility/Bitfield.hpp"

namespace Utility {

    template<class EnumType>
    BitMask<EnumType>::BitMask() : m_bitField(0) {}

    template<class EnumType>
    void BitMask<EnumType>::SetBit(const EnumType& bit, bool value)
    {
        if (value)
        {
            m_bitField |= static_cast<typename std::underlying_type<EnumType>::type>(bit);
        }
        else
        {
            m_bitField &= ~static_cast<typename std::underlying_type<EnumType>::type>(bit);
        }
    }

    template<class EnumType>
    typename std::underlying_type<EnumType>::type BitMask<EnumType>::GetMask() const
    {
        return m_bitField;
    }

}

#endif