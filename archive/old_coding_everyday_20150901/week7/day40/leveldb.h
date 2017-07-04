#ifndef __DROGON_LEVELDB__
#define __DROGON_LEVELDB__

#include <string>

#include <leveldb/db.h>

class LevelDB {
public:
	typedef leveldb::Options LOptions;
	typedef leveldb::DB LDB;
	typedef leveldb::Status LStatus;
	typedef leveldb::WriteOptions LWriteOptions;
	typedef leveldb::ReadOptions LReadOptions;

	LevelDB(std::string db_name_);
	~LevelDB();
	bool Put(const std::string &key, const std::string &value);
	bool Put(const std::string &key, const std::string &value, LWriteOptions &write_options);
	bool Get(const std::string &key, std::string &value);
	bool Get(const std::string &key, std::string &value, LReadOptions &read_options);
	bool Delete(const std::string &key);
	bool Delete(const std::string &key, LWriteOptions &write_options);
	LStatus& Status();
	LOptions& Options();
	LWriteOptions& WriteOptions();
	LReadOptions& ReadOptions();

private:
	std::string db_name_;
	LDB* db_;
	LStatus status_;
	LOptions options_;
	LWriteOptions write_options_;
	LReadOptions read_options_;
};

#endif
