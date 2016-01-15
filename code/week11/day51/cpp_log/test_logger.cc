#include "logger.h"

int main()
{
	Logger logger;
	logger.SetLevel(Logger::INFO);

	char hello[] = "Foobar.";

	logger.Info("Hello, INFO!");
	logger.Debug("Hello, DEBUG!");
	logger.Fatal(hello);

	return 0;
}
