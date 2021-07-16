#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ndn_cxx_ind
#include <boost/test/unit_test.hpp>

#include "ndn-cxx-ind.hpp"

BOOST_AUTO_TEST_CASE(cxx_ind_data_unsigned) {
    std::string name = "/one/test";
    ndn::Data cxxData(name);
    ndn_ind::Data indData = ndn::Ind::data(cxxData);
    BOOST_CHECK_EQUAL(indData.getName().toUri(), name);
}

BOOST_AUTO_TEST_CASE(cxx_ind_data_signed) {
    std::string name = "/ndn/test";
    ndn::Data cxxData(name);
    ndn::KeyChain keyChain;
    keyChain.sign(cxxData);
    cxxData.wireEncode();
    auto cxxSignBuf = cxxData.getSignatureValue().blockFromValue();

    ndn_ind::Data indData = ndn::Ind::data(cxxData);
    auto indSignBuf = indData.getSignature()->getSignature();

    BOOST_CHECK_EQUAL(indData.getName().toUri(), name);
    BOOST_CHECK_EQUAL_COLLECTIONS(cxxSignBuf.begin(), cxxSignBuf.end(),
                                  indSignBuf->begin(), indSignBuf->end());
}

BOOST_AUTO_TEST_CASE(cxx_ind_interest) {
    std::string name = "/ndn/test";
    ndn::Interest cxxInterest(name, ndn::time::milliseconds(321));
    ndn_ind::Interest indInterest = ndn::Ind::interest(cxxInterest);
    BOOST_CHECK_EQUAL(indInterest.getName().toUri(), name);
    BOOST_CHECK_EQUAL(indInterest.getInterestLifetimeMilliseconds(), 321);
}
