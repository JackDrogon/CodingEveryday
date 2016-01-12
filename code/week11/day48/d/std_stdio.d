import std.stdio;
import std.array;

int main(string[] args)
{
	char[] buf;
	size_t words = 0;

	while (!stdin.eof)
	{
		char[] line = buf;
		stdin.readln(line);
		if (line.length > buf.length)
			buf = line;

		words += line.split.length;
	}

	writeln(words);

	return 0;
}
