#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import abc
from io import StringIO
import sys


class Builder(abc.ABC):
    @abc.abstractmethod
    def make_title(self, title: str):
        pass

    @abc.abstractmethod
    def make_string(self, string: str):
        pass

    @abc.abstractmethod
    def make_items(self, items: list[str]):
        pass

    @abc.abstractmethod
    def close(self):
        pass


class TextBuilder(Builder):
    def __init__(self):
        self.buffer = StringIO()

    def make_title(self, title: str):
        self.buffer.write("====================================\n")
        self.buffer.write(f"[ {title} ]\n")
        self.buffer.write("\n")

    def make_string(self, string: str):
        self.buffer.write(f"> {string}\n")
        self.buffer.write("\n")

    def make_items(self, items: list[str]):
        for item in items:
            self.buffer.write(f"  .{item}\n")
        self.buffer.write("\n")

    def close(self):
        self.buffer.write("====================================\n")

    def get_result(self):
        return self.buffer.getvalue()


class HTMLBuilder(Builder):
    def __init__(self):
        self.filename = ""
        self.writer = None

    def make_title(self, title: str):
        self.filename = title + ".html"
        self.writer = open(self.filename, "w+")
        self.writer.write(f"<html><head><title>{title}</title></head><body>\n")
        self.writer.write(f"<h1>{title}</h1>\n")

    def make_string(self, string: str):
        self.writer.write(f"<p>{string}</p>\n")

    def make_items(self, items: list[str]):
        self.writer.write("<ul>\n")
        for item in items:
            self.writer.write(f"<li>{item}</li>\n")
        self.writer.write("</ul>\n")

    def close(self):
        self.writer.write("</body></html>\n")
        self.writer.close()

    def get_result(self):
        return self.filename


class Director:
    def __init__(self, builder: Builder):
        self.builder = builder

    def construct(self):
        self.builder.make_title("Greeting")
        self.builder.make_string("From morning to afternoon")
        self.builder.make_items(["Good morning", "Good afternoon"])
        self.builder.make_string("Evening")
        self.builder.make_items(["Good evening", "Good night", "Good bye"])
        self.builder.close()


def usage():
    print(f"{sys.argv[0]} [plain|html]")


def main():
    if len(sys.argv) != 2:
        usage()
        sys.exit(1)

    if sys.argv[1] == "plain":
        text_builder = TextBuilder()
        director = Director(text_builder)
        director.construct()
        result = text_builder.get_result()
        print(result)
    elif sys.argv[1] == "html":
        html_builder = HTMLBuilder()
        director = Director(html_builder)
        director.construct()
        result = html_builder.get_result()
        print(f"{result} write done")
    else:
        usage()
        sys.exit(1)


if __name__ == "__main__":
    main()
