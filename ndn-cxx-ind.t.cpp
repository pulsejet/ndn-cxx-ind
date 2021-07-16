#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ndn_cxx_ind
#include <boost/test/unit_test.hpp>

#include "ndn-cxx-ind.hpp"

std::string strName = "/one/test";

BOOST_AUTO_TEST_CASE(cxx_ind_data_unsigned) {
    ndn::Data cxxData(strName);
    ndn_ind::Data indData = ndn::toInd(cxxData);
    BOOST_CHECK_EQUAL(indData.getName().toUri(), strName);
}

BOOST_AUTO_TEST_CASE(cxx_ind_data_signed) {
    ndn::Data cxxData(strName);
    ndn::KeyChain keyChain;
    keyChain.sign(cxxData);
    cxxData.wireEncode();
    auto cxxSignBuf = cxxData.getSignatureValue().blockFromValue();

    ndn_ind::Data indData = ndn::toInd(cxxData);
    auto indSignBuf = indData.getSignature()->getSignature();

    BOOST_CHECK_EQUAL(indData.getName().toUri(), strName);
    BOOST_CHECK_EQUAL_COLLECTIONS(cxxSignBuf.begin(), cxxSignBuf.end(),
                                  indSignBuf->begin(), indSignBuf->end());
}

BOOST_AUTO_TEST_CASE(cxx_ind_interest) {
    ndn::Interest cxxInterest(strName, ndn::time::milliseconds(321));
    ndn_ind::Interest indInterest = ndn::toInd(cxxInterest);
    BOOST_CHECK_EQUAL(indInterest.getName().toUri(), strName);
    BOOST_CHECK_EQUAL(indInterest.getInterestLifetimeMilliseconds(), 321);
}

BOOST_AUTO_TEST_CASE(cxx_ind_name) {
    ndn::Name cxxName(strName);
    ndn_ind::Name indName = ndn::toInd(cxxName);
    BOOST_CHECK_EQUAL(indName.toUri(), strName);
}

BOOST_AUTO_TEST_CASE(ind_cxx_data) {
    ndn_ind::Data indData(strName);
    ndn::Data cxxData = ndn_ind::toCxx(indData);
    BOOST_CHECK_EQUAL(cxxData.getName().toUri(), strName);
}

BOOST_AUTO_TEST_CASE(ind_cxx_interest) {
    ndn_ind::Interest indInterest(strName, std::chrono::milliseconds(321));
    ndn::Interest cxxInterest = ndn_ind::toCxx(indInterest);
    BOOST_CHECK_EQUAL(cxxInterest.getName().toUri(), strName);
    BOOST_CHECK_EQUAL(cxxInterest.getInterestLifetime().count(), 321);
}

BOOST_AUTO_TEST_CASE(ind_cxx_name) {
    ndn_ind::Name indName(strName);
    ndn::Name cxxName = ndn_ind::toCxx(indName);
    BOOST_CHECK_EQUAL(cxxName.toUri(), strName);
}
