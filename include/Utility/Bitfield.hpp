#ifndef _H_UTILITY_BITFIELD_
#define _H_UTILITY_BITFIELD_
#include <type_traits>

namespace Utility {

    template<class EnumType>
    struct BitMask
    {
    public:
        BitMask();
        void SetBit(const EnumType& bit, bool value);
        typename std::underlying_type<EnumType>::type GetMask() const;
    private:
        typename std::underlying_type<EnumType>::type m_bitField;
    };

}

#include "Utility/Bitfield.inl"
#endif