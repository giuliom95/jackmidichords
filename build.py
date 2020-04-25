import subprocess

SRCS = [
    'src/jackmidichords.c'
]

TGT = 'bin/jackmidichords'

DEPS = [
    'jack'
]

FLAGS = [
    '-O3',
    '-ffast-math',
    '-lm'
]

cflags = []
libs = []

for dep in DEPS:
    ret = subprocess.run(['pkg-config', '--cflags', dep], stdout=subprocess.PIPE)
    cflag = ret.stdout.decode().rstrip()
    if cflag != '':
        cflags.append(cflag)

    ret = subprocess.run(['pkg-config', '--libs', dep], stdout=subprocess.PIPE)
    lib = ret.stdout.decode().rstrip()
    if lib != '':
        libs.append(lib)


cc = ['gcc']
cc += ['-o', TGT]
cc += SRCS
cc += FLAGS
cc += cflags
cc += libs

print(' '.join(cc))
subprocess.run(cc)
