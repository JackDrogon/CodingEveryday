#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
	{
		// c_str && data
		std::string const s("Emplary");
		assert(s.size() == std::strlen(s.c_str()));
		assert(std::equal(s.begin(), s.end(), s.c_str()));
		assert(std::equal(s.c_str(), s.c_str() + s.size(), s.begin()));
		assert(0 == *(s.c_str() + s.size()));
	}


	{
		std::string str1 = "45";
		std::string str2 = "3.14159";
		std::string str3 = "31337 with words";
		std::string str4 = "words and 2";

		int myint1 = std::stoi(str1);
		int myint2 = std::stoi(str2);
		int myint3 = std::stoi(str3);
		// error: 'std::invalid_argument'
		// int myint4 = std::stoi(str4);

		std::cout << "std::stoi(\"" << str1 << "\") is " << myint1 << '\n';
		std::cout << "std::stoi(\"" << str2 << "\") is " << myint2 << '\n';
		std::cout << "std::stoi(\"" << str3 << "\") is " << myint3 << '\n';
		//std::cout << "std::stoi(\"" << str4 << "\") is " << myint4 << '\n';
	}



	{
		double f = 23.43;
		std::string f_str = std::to_string(f);
		std::cout << f_str << '\n';
	}



	{
		// cpp14 -std=c++1y
		using namespace std::string_literals;

		std::string s2 = "abc\0\0def"; // forms the string "abc"
		std::string s1 = "abc\0\0def"s; // form the string "abc\0\0def"



		std::string s = "Stand back! I've got jimmies!";
		std::hash<std::string> hash_fn;

		size_t hash = hash_fn(s);

		std::cout << hash << '\n';
	}



	// front
	// front requires that empty() == false, otherwise the result is undefined.
	{
		std::string s("Exemplary");
		char& f = s.front();
		f = 'e';
		std::cout << s << '\n'; // "exemplary"
	}

	{
		std::string const c("Exemplary");
		char const& f = c.front();
		std::cout << &f << '\n'; // "Exemplary"
	}



	// back
	// back requires that empty() == false, otherwise the result is undefined.
	{
		std::string s("Exemplary");
		char& back = s.back();
		back = 's';
		std::cout << s << '\n'; // "Exemplars"
	}

	{
		std::string const c("Exemplary");
		char const& back = c.back();
		std::cout << back << '\n'; // 'y'
	}


	// shrink_to_fit
	{
		std::string s;
		std::cout << "Default-constructed capacity is " << s.capacity() << '\n';
		s.resize(100);
		std::cout << "Capacity of a 100-element string is " << s.capacity() << '\n';
		s.clear();
		std::cout << "Capacity after clear() is " << s.capacity() << '\n';
		s.shrink_to_fit();
		std::cout << "Capacity after shrink_to_fit() is " << s.capacity() << '\n';
	}

	return 0;
}
