import telebot, os
from telebot import types

TOKEN = 'your_token'

bot = telebot.TeleBot(TOKEN)

@bot.message_handler(commands=['help', 'start'])
def start(message):
    user = message.from_user.id
    markup = types.ReplyKeyboardMarkup()
    markup.add('equation')
    msg = bot.reply_to(message, 'Что делать?', reply_markup=markup)
    bot.register_next_step_handler(msg, choose)
    
def choose(message):
    user = message.from_user.id
    if message.text == "equation":
        equation(message)
    else:
        bot.send_message(user, "Я тебя не понимаю. Напиши /help.")

def equation(message):
    user = message.from_user.id
    bot.send_message(user, "Введите количество неизвестных и матрицу коэффицентов в одном сообщении\nНапрмер:\n3\n5 3 7 15\n1 0 2 3\n6 -1 3 8\nЭто будет означать систему\n5x + 3y + 7z = 15\n1x + 0y + 2z = 3\n6x + (-1)y + 3z = 8")
    bot.register_next_step_handler(message, equation_prog)

def equation_prog(message):
    user = message.from_user.id
    with open("/math/matrix.txt", "w") as file:
        for i in message.text:
            print("i = ", i)
            file.write(i)
    bot.send_message(user, 'Решаем...')
    os.system("/math/Gauss.out")
    bot.send_message(user, 'Гаусс')
    with open("/math/result.txt", "r") as file:
        for i in file: 
            bot.send_message(user, i)
        
    bot.send_message(user, 'Крамер')
    os.system("/math/Kramer.out")
    with open("/math/result.txt", "r") as file:
        for i in file:
            bot.send_message(user, i)
    start(message)


bot.infinity_polling()

