#include <ndn-cxx/data.hpp>
#include <ndn-ind/data.hpp>
#include <ndn-cxx/security/key-chain.hpp>

namespace ndn {

class Ind
{
public:
    static ndn_ind::Data
    data(const Data& data)
    {
        Block wire = signData(data).wireEncode();
        std::vector<uint8_t> wireVec(wire.wire(), wire.wire() + wire.size());
        ndn_ind::Data indData;
        indData.wireDecode(wireVec);
        return indData;
    }

private:
    static Data
    signData(const Data& data)
    {
        if (data.getSignatureInfo())
            return data;

        Data signedData(data);
        KeyChain keyChain;
        keyChain.sign(signedData);
        return signedData;
    }
};

} // namespace ndn

namespace ndn_ind {

class Cxx
{

};

} // namespace ndn_ind
