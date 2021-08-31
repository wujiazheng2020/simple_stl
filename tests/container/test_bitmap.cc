/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_bitmap.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/container/bitmap/bitmap.h"

TEST(BIT_MAP, BitMapBasic) {
  sstl::Bitmap bitmap(1000);
  bitmap.Set(8);

  LOG(INFO) << bitmap.Test(8);
  EXPECT_EQ(bitmap.Test(8), 1);

  bitmap.Set(1001);
  LOG(INFO) << bitmap.Test(1001);
  EXPECT_EQ(bitmap.Test(1001), 1);
  EXPECT_EQ(bitmap.Test(1002), 0);

  bitmap.Clear(1001);
  EXPECT_EQ(bitmap.Test(1001), 0);
  EXPECT_EQ(bitmap.Test(1002), 0);
  EXPECT_EQ(bitmap.Test(-1), 0);
}
