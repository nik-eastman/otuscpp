#include "ip_address.h"
#include <gtest/gtest.h>
 
TEST(FromString, from_string) {
    ASSERT_EQ(ipv4::from_string("0.0.0.0"), ipv4::container_type({0,0,0,0}));

    ASSERT_EQ(ipv4::from_string("0.0.0.1"), ipv4::container_type({0,0,0,1}));
    ASSERT_EQ(ipv4::from_string("0.0.1.0"), ipv4::container_type({0,0,1,0}));
    ASSERT_EQ(ipv4::from_string("0.1.0.0"), ipv4::container_type({0,1,0,0}));
    ASSERT_EQ(ipv4::from_string("1.0.0.0"), ipv4::container_type({1,0,0,0}));

    ASSERT_EQ(ipv4::from_string("255.255.255.255"), ipv4::container_type({255,255,255,255}));

    ASSERT_EQ(ipv4::from_string("0.0.0.255"), ipv4::container_type({0,0,0,255}));
    ASSERT_EQ(ipv4::from_string("0.0.255.0"), ipv4::container_type({0,0,255,0}));
    ASSERT_EQ(ipv4::from_string("0.255.0.0"), ipv4::container_type({0,255,0,0}));
    ASSERT_EQ(ipv4::from_string("255.0.0.0"), ipv4::container_type({255,0,0,0}));

    ASSERT_EQ(ipv4::from_string("1.2.3.4")        , ipv4::container_type({1,2,3,4}));
    ASSERT_EQ(ipv4::from_string("255.254.253.252"), ipv4::container_type({255,254,253,252}));
}

TEST(FromString, from_string_error) {
    // too short
    ASSERT_THROW(ipv4::from_string("1"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.3"), std::invalid_argument);

    // empty octets
    ASSERT_THROW(ipv4::from_string(".1.2.3"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1..2.3"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2..3"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.3.."), std::invalid_argument);

    // too big octet's value
    ASSERT_THROW(ipv4::from_string("256.2.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.256.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.256.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.3.256"), std::invalid_argument);

    // too long octet's string
    ASSERT_THROW(ipv4::from_string("1256.2.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.1256.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.1256.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.3.1256"), std::invalid_argument);

    // unsupported symbols
    ASSERT_THROW(ipv4::from_string("-1.2.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.+2.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.3:.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.3.4*"), std::invalid_argument);

    // last symbol is delimiter
    ASSERT_THROW(ipv4::from_string("1.2.3.4."), std::invalid_argument);

    // too many octets
    ASSERT_THROW(ipv4::from_string("1.2.3.4.5"), std::invalid_argument);
}
 
TEST(ToString, to_string) {
    ASSERT_EQ("0.0.0.0", ipv4::to_string(ipv4::container_type({0,0,0,0})));

    ASSERT_EQ("0.0.0.1", ipv4::to_string(ipv4::container_type({0,0,0,1})));
    ASSERT_EQ("0.0.1.0", ipv4::to_string(ipv4::container_type({0,0,1,0})));
    ASSERT_EQ("0.1.0.0", ipv4::to_string(ipv4::container_type({0,1,0,0})));
    ASSERT_EQ("1.0.0.0", ipv4::to_string(ipv4::container_type({1,0,0,0})));

    ASSERT_EQ("255.255.255.255", ipv4::to_string(ipv4::container_type({255,255,255,255})));

    ASSERT_EQ("0.0.0.255", ipv4::to_string(ipv4::container_type({0,0,0,255})));
    ASSERT_EQ("0.0.255.0", ipv4::to_string(ipv4::container_type({0,0,255,0})));
    ASSERT_EQ("0.255.0.0", ipv4::to_string(ipv4::container_type({0,255,0,0})));
    ASSERT_EQ("255.0.0.0", ipv4::to_string(ipv4::container_type({255,0,0,0})));

    ASSERT_EQ("1.2.3.4"        , ipv4::to_string(ipv4::container_type({1,2,3,4})));
    ASSERT_EQ("255.254.253.252", ipv4::to_string(ipv4::container_type({255,254,253,252})));
}

TEST(Compare, less) {
    // compare with 0.0.0.0
    ASSERT_TRUE(ipv4::container_type({0,0,0,0}) < ipv4::container_type({0,0,0,1}));
    ASSERT_TRUE(ipv4::container_type({0,0,0,0}) < ipv4::container_type({0,0,1,0}));
    ASSERT_TRUE(ipv4::container_type({0,0,0,0}) < ipv4::container_type({0,1,0,0}));
    ASSERT_TRUE(ipv4::container_type({0,0,0,0}) < ipv4::container_type({1,0,0,0}));

    // compare with 255.255.255.255
    ASSERT_TRUE(ipv4::container_type({255,255,255,254}) < ipv4::container_type({255,255,255,255}));
    ASSERT_TRUE(ipv4::container_type({255,255,254,255}) < ipv4::container_type({255,255,255,255}));
    ASSERT_TRUE(ipv4::container_type({255,254,255,255}) < ipv4::container_type({255,255,255,255}));
    ASSERT_TRUE(ipv4::container_type({254,255,255,255}) < ipv4::container_type({255,255,255,255}));

    // compare the same values
    ASSERT_FALSE(ipv4::container_type({0,0,0,0}) < ipv4::container_type({0,0,0,0}));
    ASSERT_FALSE(ipv4::container_type({255,255,255,255}) < ipv4::container_type({255,255,255,255}));
}

TEST(Compare, test_octet) {
    // test one octet
    ipv4::container_type ip1{1,2,3,4};
    ASSERT_TRUE(std::get<0>(ip1) == 1);
    ASSERT_TRUE(std::get<1>(ip1) == 2);
    ASSERT_TRUE(std::get<2>(ip1) == 3);
    ASSERT_TRUE(std::get<3>(ip1) == 4);

    // test any octet
    ipv4::container_type ip2{255,254,253,252};
    ASSERT_TRUE(std::any_of(ip2.cbegin(), ip2.cend(), [](const auto& octet) { return octet == 252; }));
    ASSERT_TRUE(std::any_of(ip2.cbegin(), ip2.cend(), [](const auto& octet) { return octet == 253; }));
    ASSERT_TRUE(std::any_of(ip2.cbegin(), ip2.cend(), [](const auto& octet) { return octet == 254; }));
    ASSERT_TRUE(std::any_of(ip2.cbegin(), ip2.cend(), [](const auto& octet) { return octet == 255; }));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}