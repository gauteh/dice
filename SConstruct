env = Environment ()

env.ParseConfig ('pkg-config --cflags --libs gtk+-2.0')
env.AppendUnique (CCFLAGS = ['-g','-DDEBUG'])

source_files = [ 'dice.c', ]

env.Program (target = 'dice', source = source_files)

