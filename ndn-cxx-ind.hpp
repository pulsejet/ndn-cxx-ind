#include <ndn-cxx/data.hpp>
#include <ndn-ind/data.hpp>
#include <ndn-cxx/interest.hpp>
#include <ndn-ind/interest.hpp>
#include <ndn-cxx/security/key-chain.hpp>

#ifndef NDN_CXX_IND_HPP
#define NDN_CXX_IND_HPP

namespace ndn {

struct IndInternal
{
    static Data
    signData(const Data& data)
    {
        if (data.getSignatureInfo())
            return data;

        Data signedData(data);
        KeyChain keyChain("pib-memory:", "tpm-memory:");
        keyChain.sign(signedData);
        return signedData;
    }

    template <class C, class N>
    static N
    conv(const C& cxxInp)
    {
        Block wire = cxxInp.wireEncode();
        std::vector<uint8_t> wireVec(wire.wire(), wire.wire() + wire.size());
        N indOut;
        indOut.wireDecode(wireVec);
        return indOut;
    }
};

inline ndn_ind::Data
toInd(const Data& data)
{
    return IndInternal::conv<Data, ndn_ind::Data>(IndInternal::signData(data));
}

inline ndn_ind::Interest
toInd(const Interest& interest)
{
    return IndInternal::conv<Interest, ndn_ind::Interest>(interest);
}

inline ndn_ind::Name
toInd(const Name& name)
{
    return IndInternal::conv<Name, ndn_ind::Name>(name);
}

} // namespace ndn

namespace ndn_ind {

struct CxxInternal
{

};

inline ndn::Data
toCxx(const Data& cxxInp)
{
    auto wire = cxxInp.wireEncode();
    ndn::Data indOut;
    indOut.wireDecode(ndn::Block(wire.buf(), wire.size()));
    return indOut;
}

} // namespace ndn_ind

#endif
