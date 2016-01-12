import std.algorithm;
import std.array;
import std.csv;
import std.stdio;
import std.typecons;

void main()
{
	auto text = "Joe,Carpenter,300000\nFred,Blacksmith,400000\r\n";

	foreach(record; csvReader!(Tuple!(string, string, int))(text))
	{
		writefln("%s works as a %s and earns $%d per year",
				record[0], record[1], record[2]);
	}

	// To read the same string from the file "filename.csv":

	auto file = File("filename.csv", "r");
	foreach(record;
			file.byLine.joiner("\n").csvReader!(Tuple!(string, string, int)))
	{
		writefln("%s works as a %s and earns $%d per year",
				record[0], record[1], record[2]);
	}
}
