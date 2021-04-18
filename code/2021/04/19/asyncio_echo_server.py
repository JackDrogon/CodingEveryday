#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import asyncio


async def handle_echo(reader, writer):
    addr = writer.get_extra_info('peername')

    data = await reader.read(100)
    message = data.decode()

    print(f"Received {message!r} from {addr!r}")

    print(f"Send: {message!r}")
    writer.write(data)
    await writer.drain()

    print('Close connection')
    writer.close()


async def asyncio_tcp_server():
    host = "127.0.0.1"
    port = 1234
    server = await asyncio.start_server(handle_echo, host, port)

    async with server:
        await server.serve_forever()


def main():
    asyncio.run(asyncio_tcp_server())


if __name__ == "__main__":
    main()
