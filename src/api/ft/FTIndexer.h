#ifndef __DFS_UTIL_FILE_TIMESTAMP_INDEXER_H__
#define __DFS_UTIL_FILE_TIMESTAMP_INDEXER_H__

#include <string>
#include <unordered_map>
#include "api/fs/timestamp.h"
#include "FTIndex.h"


typedef std::unordered_map<std::string, timestamp_t>::iterator ftIterator_t;


class FTIndexerTest;

class FTIndexer {
private:
    FTIndex* m_indexObject;

public:
    FTIndexer(FTIndex* index);

    timestamp_t at(const std::string& fileName);
    bool contains(const std::string& fileName);

    void insert(const std::string& fileName, const timestamp_t& timestamp);
    void erase(const std::string& fileName);

    friend FTIndexerTest;
};


#endif // __DFS_UTIL_FILE_TIMESTAMP_INDEXER_H__
