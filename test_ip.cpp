#include "ip_address.h"
#include <gtest/gtest.h>
 
TEST(FromString, from_string) {
    ASSERT_EQ(ipv4::from_string("0.0.0.0"), ipv4(0x00000000));

    ASSERT_EQ(ipv4::from_string("0.0.0.1"), ipv4(0x00000001));
    ASSERT_EQ(ipv4::from_string("0.0.1.0"), ipv4(0x00000100));
    ASSERT_EQ(ipv4::from_string("0.1.0.0"), ipv4(0x00010000));
    ASSERT_EQ(ipv4::from_string("1.0.0.0"), ipv4(0x01000000));

    ASSERT_EQ(ipv4::from_string("255.255.255.255"), ipv4(0xffffffff));

    ASSERT_EQ(ipv4::from_string("0.0.0.255"), ipv4(0x000000ff));
    ASSERT_EQ(ipv4::from_string("0.0.255.0"), ipv4(0x0000ff00));
    ASSERT_EQ(ipv4::from_string("0.255.0.0"), ipv4(0x00ff0000));
    ASSERT_EQ(ipv4::from_string("255.0.0.0"), ipv4(0xff000000));

    ASSERT_EQ(ipv4::from_string("1.2.3.4")        , ipv4(0x01020304));
    ASSERT_EQ(ipv4::from_string("255.254.253.252"), ipv4(0xfffefdfc));
}

TEST(FromString, from_string_error) {
    // too short
    ASSERT_THROW(ipv4::from_string("1"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.3"), std::invalid_argument);

    // too short octet
    ASSERT_THROW(ipv4::from_string(".1.2.3"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1..2.3"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2..3"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.3.."), std::invalid_argument);

    // to big octet value
    ASSERT_THROW(ipv4::from_string("256.2.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.256.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.256.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.3.256"), std::invalid_argument);

    // too large octet value
    ASSERT_THROW(ipv4::from_string("256.2.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.256.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.256.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.3.256"), std::invalid_argument);

    // too large octet value
    ASSERT_THROW(ipv4::from_string("1256.2.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.1256.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.1256.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.3.1256"), std::invalid_argument);

    // too large octet length
    ASSERT_THROW(ipv4::from_string("1256.2.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.1256.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.1256.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.3.1256"), std::invalid_argument);

    // unsupported symbols
    ASSERT_THROW(ipv4::from_string("-1256.2.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.+1256.3.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.1256+.4"), std::invalid_argument);
    ASSERT_THROW(ipv4::from_string("1.2.3.1256-"), std::invalid_argument);

    // last symbol is delimiter
    ASSERT_THROW(ipv4::from_string("1.2.3.4."), std::invalid_argument);

    // too many octets
    ASSERT_THROW(ipv4::from_string("1.2.3.4.5"), std::invalid_argument);
}
 
TEST(ToString, to_string) {
    ASSERT_EQ("0.0.0.0", ipv4(0x00000000).to_string());

    ASSERT_EQ("0.0.0.1", ipv4(0x00000001).to_string());
    ASSERT_EQ("0.0.1.0", ipv4(0x00000100).to_string());
    ASSERT_EQ("0.1.0.0", ipv4(0x00010000).to_string());
    ASSERT_EQ("1.0.0.0", ipv4(0x01000000).to_string());

    ASSERT_EQ("255.255.255.255", ipv4(0xffffffff).to_string());

    ASSERT_EQ("0.0.0.255", ipv4(0x000000ff).to_string());
    ASSERT_EQ("0.0.255.0", ipv4(0x0000ff00).to_string());
    ASSERT_EQ("0.255.0.0", ipv4(0x00ff0000).to_string());
    ASSERT_EQ("255.0.0.0", ipv4(0xff000000).to_string());

    ASSERT_EQ("1.2.3.4"        , ipv4(0x01020304).to_string());
    ASSERT_EQ("255.254.253.252", ipv4(0xfffefdfc).to_string());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}