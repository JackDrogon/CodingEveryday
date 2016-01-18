#include "logger.h"

int main()
{
	Logger logger("test_file_log.log");
	logger.SetLevel(Logger::INFO);

	char hello[] = "Foobar.";

	logger.Info("Hello, INFO!");
	logger.Debug("Hello, DEBUG!");
	logger.Fatal(hello);

	return 0;
}
