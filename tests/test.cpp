// Copyright 2019 Kirill <your_email>

#include <gtest/gtest.h>
#include <header.hpp>

TEST(Example, EmptyTest) {
    auto curr_path = boost::filesystem::current_path();
    string str_curr_path = curr_path.string();
    if (str_curr_path.find("sources") != string::npos)
    {
        str_curr_path.erase(str_curr_path.rfind("/"),
                        str_curr_path.length() - 1);
        str_curr_path += string("/misc/ftp");
    }
    auto path_ftp = boost::filesystem::path{str_curr_path.c_str()};
    my_FTP result(path_ftp);
    EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
