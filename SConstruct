env = Environment ()
env.ParseConfig ('pkg-config --cflags --libs gtk+-2.0')

source_files = [ 'dice.c', ]

env.AppendUnique (CCFLAGS = ['-g','-DDEBUG'])
env.Program (target = 'dice', source = source_files)

