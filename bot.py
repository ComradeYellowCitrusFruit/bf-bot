import discord
import sys

TOKEN = sys.argv[0]

class botClient(discord.Client):
    async def on_message(self, message):
        if message.author == self.user:
            return

        if message.content[0] == '!':
            print(message.content)
            if message.content[1] == 'v':
                await message.channel.send(input())
            else:
                return
        else:
            return

bot = botClient()
bot.run(TOKEN)