###############################################################################
#
# Configuration file for ikos
#
# Author: Maxime Arthaud
#
# Contact: ikos@lists.nasa.gov
#
# Notices:
#
# Copyright (c) 2017-2019 United States Government as represented by the
# Administrator of the National Aeronautics and Space Administration.
# All Rights Reserved.
#
# Disclaimers:
#
# No Warranty: THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY OF
# ANY KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT LIMITED
# TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO SPECIFICATIONS,
# ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
# OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL BE
# ERROR FREE, OR ANY WARRANTY THAT DOCUMENTATION, IF PROVIDED, WILL CONFORM TO
# THE SUBJECT SOFTWARE. THIS AGREEMENT DOES NOT, IN ANY MANNER, CONSTITUTE AN
# ENDORSEMENT BY GOVERNMENT AGENCY OR ANY PRIOR RECIPIENT OF ANY RESULTS,
# RESULTING DESIGNS, HARDWARE, SOFTWARE PRODUCTS OR ANY OTHER APPLICATIONS
# RESULTING FROM USE OF THE SUBJECT SOFTWARE.  FURTHER, GOVERNMENT AGENCY
# DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING THIRD-PARTY SOFTWARE,
# IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES IT "AS IS."
#
# Waiver and Indemnity:  RECIPIENT AGREES TO WAIVE ANY AND ALL CLAIMS AGAINST
# THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL
# AS ANY PRIOR RECIPIENT.  IF RECIPIENT'S USE OF THE SUBJECT SOFTWARE RESULTS
# IN ANY LIABILITIES, DEMANDS, DAMAGES, EXPENSES OR LOSSES ARISING FROM SUCH
# USE, INCLUDING ANY DAMAGES FROM PRODUCTS BASED ON, OR RESULTING FROM,
# RECIPIENT'S USE OF THE SUBJECT SOFTWARE, RECIPIENT SHALL INDEMNIFY AND HOLD
# HARMLESS THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS,
# AS WELL AS ANY PRIOR RECIPIENT, TO THE EXTENT PERMITTED BY LAW.
# RECIPIENT'S SOLE REMEDY FOR ANY SUCH MATTER SHALL BE THE IMMEDIATE,
# UNILATERAL TERMINATION OF THIS AGREEMENT.
#
###############################################################################
import argparse
import os
import os.path
import sys

PACKAGE_VERSION = '3.1'

GIT_COUNT_COMMITS = ''

GIT_HEAD_HASH = ''

GIT_HEAD_DIRTY = False

APPEND_GIT_VERSION = (GIT_COUNT_COMMITS and GIT_HEAD_HASH)

VERSION = PACKAGE_VERSION

if APPEND_GIT_VERSION:
    VERSION += '.r%s' % GIT_COUNT_COMMITS
    VERSION += '.%s' % GIT_HEAD_HASH
    if GIT_HEAD_DIRTY:
        VERSION += '~dirty'

BUILD_MODE = 'Debug'

PREFIX = '/home/zou/Documents/DFIKOS/install'

SRC_ROOT = '/home/zou/Documents/DFIKOS/analyzer'

BIN_DIR = os.path.join(PREFIX, 'bin')

INCLUDE_DIR = os.path.join(PREFIX, 'include')

LIB_DIR = os.path.join(PREFIX, 'lib')

LLVM_CONFIG = '/usr/bin/llvm-config-14'

LLVM_VERSION = '14.0.6'

LLVM_PREFIX = '/usr/lib/llvm-14'

LLVM_BIN_DIR = '/usr/lib/llvm-14/bin'

LLVM_INCLUDE_DIR = '/usr/lib/llvm-14/include'

LLVM_LIB_DIR = '/usr/lib/llvm-14/lib'

CLANG = '/usr/lib/llvm-14/bin/clang'

CLANGXX = '/usr/lib/llvm-14/bin/clang++'

CLANG_VERSION = '14.0.6'

HAS_APRON = True


####################
# Helper functions #
####################


def is_executable(path):
    return path and os.path.isfile(path) and os.access(path, os.X_OK)


def clang():
    path = CLANG
    assert os.path.isabs(path)
    assert is_executable(path), 'could not find clang executable'
    return path


def clangxx():
    path = CLANGXX
    assert os.path.isabs(path)
    assert is_executable(path), 'could not find clang++ executable'
    return path


def opt():
    path = os.path.join(LLVM_BIN_DIR, 'opt')
    assert os.path.isabs(path)
    assert is_executable(path), 'could not find opt executable'
    return path


def llvm_link():
    path = os.path.join(LLVM_BIN_DIR, 'llvm-link')
    assert os.path.isabs(path)
    assert is_executable(path), 'could not find llvm-link executable'
    return path


def llvm_objdump():
    path = os.path.join(LLVM_BIN_DIR, 'llvm-objdump')
    assert os.path.isabs(path)
    assert is_executable(path), 'could not find llvm-objdump executable'
    return path


def llvm_objcopy():
    path = os.path.join(LLVM_BIN_DIR, 'llvm-objcopy')
    assert os.path.isabs(path)
    assert is_executable(path), 'could not find llvm-objcopy executable'
    return path


def ikos_pp():
    path = os.path.join(BIN_DIR, 'ikos-pp')
    assert os.path.isabs(path)
    assert is_executable(path), 'could not find ikos-pp executable'
    return path


def ikos_analyzer():
    path = os.path.join(BIN_DIR, 'ikos-analyzer')
    assert os.path.isabs(path)
    assert is_executable(path), 'could not find ikos-analyzer executable'
    return path


def ikos():
    path = os.path.join(BIN_DIR, 'ikos')
    assert os.path.isabs(path)
    assert is_executable(path), 'could not find ikos python script'
    return path


########################
# main for ikos-config #
########################


def main(argv):
    usage = '%(prog)s [options]'
    description = 'Get configuration information about ikos'
    parser = argparse.ArgumentParser(usage=usage,
                                     description=description)

    def print_action(var):
        class action(argparse.Action):
            def __call__(self, parser, namespace, values, option_string=None):
                print(str(var))

        return action

    parser.add_argument('--version', action=print_action(VERSION), nargs=0,
                        help='Print ikos version')
    parser.add_argument('--build-mode', action=print_action(BUILD_MODE), nargs=0,
                        help='Print build mode of ikos (e.g, Debug or Release)')
    parser.add_argument('--prefix', action=print_action(PREFIX), nargs=0,
                        help='Print the installation prefix')
    parser.add_argument('--src-root', action=print_action(SRC_ROOT), nargs=0,
                        help='Print the source root ikos was built from')
    parser.add_argument('--bindir', action=print_action(BIN_DIR), nargs=0,
                        help='Directory containing ikos executables')
    parser.add_argument('--includedir', action=print_action(INCLUDE_DIR), nargs=0,
                        help='Directory containing ikos headers')
    parser.add_argument('--libdir', action=print_action(LIB_DIR), nargs=0,
                        help='Directory containing ikos libraries')
    parser.add_argument('--has-apron', action=print_action(HAS_APRON), nargs=0,
                        help='Check if ikos was built with apron')
    parser.add_argument('--llvm-config', action=print_action(LLVM_CONFIG), nargs=0,
                        help='Print the path to llvm-config')
    parser.add_argument('--llvm-version', action=print_action(LLVM_VERSION), nargs=0,
                        help='Print LLVM version')
    parser.add_argument('--llvm-prefix', action=print_action(LLVM_PREFIX), nargs=0,
                        help='Print the LLVM installation prefix')
    parser.add_argument('--llvm-bindir', action=print_action(LLVM_BIN_DIR), nargs=0,
                        help='Directory containing LLVM executables')
    parser.add_argument('--llvm-includedir', action=print_action(LLVM_INCLUDE_DIR), nargs=0,
                        help='Directory containing LLVM headers')
    parser.add_argument('--llvm-libdir', action=print_action(LLVM_LIB_DIR), nargs=0,
                        help='Directory containing LLVM libraries')
    parser.add_argument('--clang', action=print_action(CLANG), nargs=0,
                        help='Print the path to clang')
    parser.add_argument('--clang-version', action=print_action(CLANG_VERSION), nargs=0,
                        help='Print clang version')

    parser.parse_args(argv[1:])
