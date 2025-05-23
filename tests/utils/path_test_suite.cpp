// Copyright (c) 2014-2022 Thomas Fussell
// Copyright (c) 2024-2025 xlnt-community
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE
//
// @license: http://www.opensource.org/licenses/mit-license.php
// @author: see AUTHORS file

#include <xlnt/utils/path.hpp>
#include <detail/utils/string_helpers.hpp>
#include <helpers/path_helper.hpp>
#include <helpers/temporary_file.hpp>
#include <helpers/test_suite.hpp>

class path_test_suite : public test_suite
{
public:
    path_test_suite()
    {
        register_test(test_exists);
#ifdef _MSC_VER
        register_test(test_msvc_empty_path_wide);
#endif
        register_test(test_append);
#if XLNT_HAS_FEATURE(U8_STRING_VIEW)
        register_test(test_append_u8);
#endif
    }

    void test_exists()
    {
        temporary_file temp;

        if (temp.get_path().exists())
        {
            path_helper::delete_file(temp.get_path());
        }

        xlnt_assert(!temp.get_path().exists());
        std::ofstream stream(temp.get_path().string());
        xlnt_assert(temp.get_path().exists());
    }

#ifdef _MSC_VER
    void test_msvc_empty_path_wide()
    {
        xlnt::path empty_path;
        std::wstring path_wide;
        xlnt_assert_throws_nothing(path_wide = empty_path.wstring());
        xlnt_assert(path_wide.empty());
    }
#endif

    void test_append()
    {
        xlnt::path path("hello");
        path = path.append("world");
        xlnt_assert_equals(path.string(), "hello/world");
    }

#if XLNT_HAS_FEATURE(U8_STRING_VIEW)
    void test_append_u8()
    {
        xlnt::path path(u8"🤔🥳😇");
        path = path.append(u8"🍕🍟🍔");
        xlnt_assert_equals(path.string(), U8_TO_CHAR_PTR(u8"🤔🥳😇/🍕🍟🍔"));
    }
#endif

};
static path_test_suite x;
