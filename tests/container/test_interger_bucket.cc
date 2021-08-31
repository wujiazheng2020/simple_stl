/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_interger_bucket.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/container/bucket/interger_bucket.h"

TEST(TEST_INTERGER_BUCKET, TEST_BUCKET_USAGE) {
  sstl::IntergerBucket bucket;
  bucket.Set(5);
  bucket.Set(5);
  EXPECT_EQ(bucket.GetAcc(5), 2);
  EXPECT_EQ(bucket.Test(5), true);
}
