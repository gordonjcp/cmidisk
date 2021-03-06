#! /usr/bin/env python

# the following two variables are used by the target "waf dist"
VERSION='0.1'
APPNAME='cmitool'

# these variables are mandatory ('/' are converted automatically)
top = '.'
out = 'build'

def options(opt):
    opt.load('compiler_cc')

def configure(conf):
    conf.load('compiler_cc')
    conf.check(header_name='stdlib.h')
    conf.check(header_name='stdio.h')
    conf.check(lib="sndfile")
    
    # set for debugging
    conf.env.CFLAGS = ['-O0', '-g3', '-ggdb', '-Wall', '-Werror']

    
def build(bld):
    # the main program
    bld(
        features = 'c cprogram',
        source = ['cmidisk.c', 'imd.c', 'snd.c'],
        target = APPNAME,
        use = ['SNDFILE'] ,
        includes = '. /usr/include')
    bld(
        features = 'c cprogram',
        source = ['unimd.c', 'imd.c', ],
        target = "unimd",
        includes = '. /usr/include')

