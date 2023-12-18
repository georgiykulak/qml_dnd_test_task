import asyncio
import random


HOST, PORT = "localhost", 8080
INTERVAL = 0.2
COLORS = "red", "yellow", "gold", "green", "blue", "white", "black"


async def handler(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    try:
        print("Connection opened.")
        while True:
            command = await reader.readline()
            command = command.decode("utf-8").strip()
            await asyncio.sleep(INTERVAL)

            if command == "next":
                data = random.choice(COLORS) + "\n"
                writer.write(data.encode("utf-8"))
                await writer.drain()
            elif command == "stop":
                break
    finally:
        writer.close()
        await writer.wait_closed()
        print("Connection closed.")


async def main():
    server = await asyncio.start_server(handler, HOST, PORT)
    async with server:
        await server.serve_forever()


if __name__ == "__main__":
    print(f"Running on {HOST}:{PORT}")
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass
