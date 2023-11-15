#include <stdlib.h>
#include <lab.h>
#include <gtest/gtest.h>
#include <algorithm>

/**
 * @brief Test Fixture that will create an array that is randomly populated
 *
 */
class UnSortedArrayLarge : public testing::Test
{
protected:
     void SetUp() override
     {
          A_ = new int[defaultSize_];
          srandom(defaultSeed_);
          for (int i = 0; i < defaultSize_; i++)
               A_[i] = random() % defaultRange_;
          // Make sure that the array is unsorted
          bool rval = std::is_sorted(A_, A_ + defaultSize_);
          EXPECT_FALSE(rval);
     }

     void TearDown() override
     {
          delete[] A_;
     }

     int defaultRange_ = 1000000;
     int defaultSize_ = 1000000;
     int defaultSeed_ = 1;
     int *A_ = nullptr;
};

/**
 * @brief Test Fixture that will create an array that is populated with
 * a known small sequence that can make debugging easier
 *
 */
class UnSortedArraySmall : public testing::Test
{
protected:
     void SetUp() override
     {
          bool rval = std::is_sorted(A_, A_ + size_);
          EXPECT_FALSE(rval);
          rval = std::is_sorted(A_odd_, A_odd_ + size_);
          EXPECT_FALSE(rval);
     }

     void TearDown() override
     {
          // We what to make sure we didn't loose any elements
          // when sorting. For example if we clobber an element (duplicated it)
          // the array would still be sorted but missing data.
          for (int i = 0; i < size_; i++)
          {
               EXPECT_EQ(A_[i], A_sorted[i]);
          }

          for (int i = 0; i < size_; i++)
          {
               EXPECT_EQ(A_odd_[i], A_odd_sorted[i]);
          }
     }
     // even size array
     static const int size_ = 10;
     int A_[size_] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
     int A_sorted[size_] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

     // Odd size array
     static const int odd_ = 13;
     int A_odd_[odd_] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
     int A_odd_sorted[odd_] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
};

TEST_F(UnSortedArraySmall, mergesort_sm_sorted)
{
     //Test to make sure a sorted array stays sorted
     mergesort_sm(A_sorted, 0, size_ - 1,1);
     mergesort_sm(A_, 0, size_ - 1,1);
     EXPECT_TRUE(std::is_sorted(A_sorted, A_sorted + size_));
     EXPECT_TRUE(std::is_sorted(A_, A_ + size_));
     mergesort_sm(A_odd_sorted, 0, odd_ - 1,1);
     mergesort_sm(A_odd_, 0, odd_ - 1,1);
     EXPECT_TRUE(std::is_sorted(A_odd_sorted, A_odd_sorted + size_));
     EXPECT_TRUE(std::is_sorted(A_odd_, A_odd_ + odd_));
}

TEST_F(UnSortedArraySmall, mergesort_mt_small_one)
{
     mergesort_mt(A_, size_, 1,1);
     bool rval = std::is_sorted(A_, A_ + size_);
     EXPECT_TRUE(rval);
     mergesort_mt(A_odd_, odd_, 1,1);
     rval = std::is_sorted(A_odd_, A_odd_ + odd_);
     EXPECT_TRUE(rval);
}

TEST_F(UnSortedArraySmall, mergesort_mt_small_two)
{
     mergesort_mt(A_, size_, 2,1);
     bool rval = std::is_sorted(A_, A_ + size_);
     EXPECT_TRUE(rval);
     mergesort_mt(A_odd_, odd_, 2,1);
     rval = std::is_sorted(A_odd_, A_odd_ + odd_);
     EXPECT_TRUE(rval);
}

TEST_F(UnSortedArraySmall, mergesort_mt_small_three)
{
     mergesort_mt(A_, size_, 3,1);
     bool rval = std::is_sorted(A_, A_ + size_);
     EXPECT_TRUE(rval);
     mergesort_mt(A_odd_, odd_, 3,1);
     rval = std::is_sorted(A_odd_, A_odd_ + odd_);
     EXPECT_TRUE(rval);
}

TEST_F(UnSortedArrayLarge, mergesort_s)
{
     mergesort_s(A_, 0, defaultSize_ - 1);
     bool rval = std::is_sorted(A_, A_ + defaultSize_);
     EXPECT_TRUE(rval);
}

TEST_F(UnSortedArrayLarge, mergesort_mt_one)
{

     mergesort_mt(A_, defaultSize_ , 1,0);
     bool rval = std::is_sorted(A_, A_ + defaultSize_);
     EXPECT_TRUE(rval);
}

TEST_F(UnSortedArrayLarge, mergesort_mt_two)
{
     mergesort_mt(A_, defaultSize_, 2,0);
     bool rval = std::is_sorted(A_, A_ + defaultSize_);
     EXPECT_TRUE(rval);
}

TEST_F(UnSortedArrayLarge, mergesort_mt_three)
{
     mergesort_mt(A_, defaultSize_, 3,0);
     bool rval = std::is_sorted(A_, A_ + defaultSize_);
     EXPECT_TRUE(rval);
}

TEST_F(UnSortedArrayLarge, mergesort_mt_four)
{
     mergesort_mt(A_, defaultSize_, 4,0);
     bool rval = std::is_sorted(A_, A_ + defaultSize_);
     EXPECT_TRUE(rval);
}