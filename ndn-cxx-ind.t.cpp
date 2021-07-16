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
