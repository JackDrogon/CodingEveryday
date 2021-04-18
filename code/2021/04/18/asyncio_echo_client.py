#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import asyncio


async def asyncio_echo_client():
    reader, writer = await asyncio.open_connection("127.0.0.1", 1234)

    msg = "PING\n"
    print(f"Send {msg}", end="")
    writer.write(msg.encode())
    await writer.drain()

    data = await reader.read(100)
    print(f"Receive {data.decode()!r}")

    print("Close connection")
    writer.close()
    await writer.wait_closed()


def main():
    asyncio.run(asyncio_echo_client())


if __name__ == "__main__":
    main()
