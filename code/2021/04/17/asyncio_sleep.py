#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import asyncio


async def asyncio_sleep():
    print("Hello,")
    await asyncio.sleep(1)
    print("World!")


def main():
    asyncio.run(asyncio_sleep())


if __name__ == "__main__":
    main()
