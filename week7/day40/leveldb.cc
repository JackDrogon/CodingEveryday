#include "leveldb.h"

LevelDB::LevelDB(std::string db_name)
	: db_name_(db_name), options_(LOptions()), write_options_(LWriteOptions()), read_options_(LReadOptions())
{
	options_.create_if_missing = true;
	status_ = leveldb::DB::Open(options_, db_name, &db_);
}

LevelDB::~LevelDB()
{
	delete db_;
}

bool LevelDB::Put(const std::string &key, const std::string &value)
{
	status_ = db_->Put(write_options_, key, value);

	return status_.ok();
}

bool LevelDB::Put(const std::string &key, const std::string &value, LWriteOptions &write_options)
{
	status_ = db_->Put(write_options, key, value);

	return status_.ok();
}

bool LevelDB::Get(const std::string &key, std::string &value)
{
	status_ = db_->Get(read_options_, key, &value);

	return status_.ok();
}

bool LevelDB::Get(const std::string &key, std::string &value, LReadOptions &read_options)
{
	status_ = db_->Get(read_options, key, &value);

	return status_.ok();
}

bool LevelDB::Delete(const std::string &key)
{
	status_ = db_->Delete(write_options_, key);

	return status_.ok();
}

bool LevelDB::Delete(const std::string &key, LWriteOptions &write_options)
{
	status_ = db_->Delete(write_options, key);

	return status_.ok();
}

LevelDB::LStatus& LevelDB::Status()
{
	return status_;
}

LevelDB::LOptions& LevelDB::Options()
{
	return options_;
}

LevelDB::LWriteOptions& LevelDB::WriteOptions()
{
	return write_options_;
}

LevelDB::LReadOptions& LevelDB::ReadOptions()
{
	return read_options_;
}
