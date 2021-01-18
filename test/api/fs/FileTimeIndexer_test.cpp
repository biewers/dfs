#include <exception>
#include <string>

#include <gtest/gtest.h>

#include "exceptions/fs.h"
#include "test-util.h"
#include "fs/FileTimeIndexer.h"
#include "FileTimeIndexer.h"


static const char* FILE_NAME{ "FileTimeIndexerAPI_randomFile" };


TEST_F(FileTimeIndexerTest, test_construction) {
    ASSERT_NO_THROW(FileTimeIndexer("test-index-file", 10));
    deleteFile("test-index-file");
}


TEST_F(FileTimeIndexerTest, test_index_single_no_timestamp) {
    createRandomFile(FILE_NAME, 100);
    ASSERT_NO_THROW(m_indexer->index(FILE_NAME));
    deleteFile(FILE_NAME);
    ASSERT_TRUE(m_indexer->contains(FILE_NAME));
}


TEST_F(FileTimeIndexerTest, test_index_multiple_no_timestamps) {
    for (int i{ 0 }; i < 10000; ++i) {
        const std::string FILE_NAME_i{ FILE_NAME + std::to_string(i) };
        createRandomFile(FILE_NAME_i, 10);
        ASSERT_NO_THROW(m_indexer->index(FILE_NAME_i));
        deleteFile(FILE_NAME_i);
        ASSERT_TRUE(m_indexer->contains(FILE_NAME_i));
    }
}


TEST_F(FileTimeIndexerTest, test_index_single_non_existant_file_no_timestamp) {
    ASSERT_THROW(m_indexer->index("invalid-file-name"), FileDoesNotExistException);
}


TEST_F(FileTimeIndexerTest, test_index_single_with_timestamp) {
    createRandomFile(FILE_NAME, 100);
    ASSERT_NO_THROW(m_indexer->index(FILE_NAME, timestamp_t()));
    deleteFile(FILE_NAME);
    ASSERT_TRUE(m_indexer->contains(FILE_NAME));
}


TEST_F(FileTimeIndexerTest, test_index_multiple_with_timestamps) {
    for (int i{ 0 }; i < 10000; ++i) {
        const std::string FILE_NAME_i{ FILE_NAME + std::to_string(i) };
        createRandomFile(FILE_NAME_i, 10);
        ASSERT_NO_THROW(m_indexer->index(FILE_NAME_i, timestamp_t()));
        deleteFile(FILE_NAME_i);
        ASSERT_TRUE(m_indexer->contains(FILE_NAME_i));
    }
}


TEST_F(FileTimeIndexerTest, test_index_single_non_existant_file_with_timestamp) {
    ASSERT_THROW(m_indexer->index("invalid-file-name", timestamp_t()), FileDoesNotExistException);
}


TEST_F(FileTimeIndexerTest, test_contains_true) {
    createRandomFile(FILE_NAME, 10);
    ASSERT_NO_THROW(m_indexer->index(FILE_NAME));
    deleteFile(FILE_NAME);
    ASSERT_TRUE(m_indexer->contains(FILE_NAME));
}


TEST_F(FileTimeIndexerTest, test_contains_false) {
    ASSERT_FALSE(m_indexer->contains(FILE_NAME));
}


TEST_F(FileTimeIndexerTest, test_get_single) {
    createRandomFile(FILE_NAME, 10);
    ASSERT_NO_THROW(m_indexer->index(FILE_NAME));
    deleteFile(FILE_NAME);
    ASSERT_NE(m_indexer->get(FILE_NAME), EMPTY_TIMESTAMP);
}


TEST_F(FileTimeIndexerTest, test_get_non_existant) {
    ASSERT_EQ(m_indexer->get(FILE_NAME), EMPTY_TIMESTAMP);
}


TEST_F(FileTimeIndexerTest, test_remove_single) {
    createRandomFile(FILE_NAME, 10);
    ASSERT_NO_THROW(m_indexer->index(FILE_NAME));
    deleteFile(FILE_NAME);
    ASSERT_TRUE(m_indexer->contains(FILE_NAME));
    ASSERT_NO_THROW(m_indexer->remove(FILE_NAME));
    ASSERT_FALSE(m_indexer->contains(FILE_NAME));
}


TEST_F(FileTimeIndexerTest, test_remove_multiple) {
    for (int i{ 0 }; i < 10000; ++i) {
        const std::string FILE_NAME_i{ FILE_NAME + std::to_string(i) };
        createRandomFile(FILE_NAME_i, 10);
        ASSERT_NO_THROW(m_indexer->index(FILE_NAME_i));
        deleteFile(FILE_NAME_i);
        ASSERT_TRUE(m_indexer->contains(FILE_NAME_i));
    }

    for (int i{ 0 }; i < 10000; ++i) {
        const std::string FILE_NAME_i{ FILE_NAME + std::to_string(i) };
        ASSERT_NO_THROW(m_indexer->remove(FILE_NAME_i));
        ASSERT_FALSE(m_indexer->contains(FILE_NAME_i));
    }
}


TEST_F(FileTimeIndexerTest, test_remove_non_existant) {
    ASSERT_NO_THROW(m_indexer->remove(FILE_NAME));
}