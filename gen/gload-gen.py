#!/usr/bin/env python3

import os
import sys
import getopt

import xml.etree.ElementTree as ET

g_path: str = os.path.dirname(__file__)
g_name: str = 'gload.h'
g_version: str = '1.0'
g_author: str = 'Jakub Oleksiak (yakubofficialmail@gmail.com)'
g_licence: str = 'GNU LESSER GENERAL PUBLIC LICENSE Version 3, 29 June 2007'

g_opts: str = 'hvo:'
g_optl: list = [
    'help',     # -h, --help
    'version',  # -v, --version
    'output=',  # -o, --output
]
g_opt: dict = {
    'output': f'{g_path}/gload.h',
    'template': f'{g_path}/gload-template.h',
}


# ===============
# SECTION: getopt
# ===============

def gl_getopt():
    global g_opt

    try:
        opts, args = getopt.getopt(sys.argv[1:], g_opts, g_optl)
    except getopt.GetoptError as err:
        print(f'{__file__}: {err}')
        sys.exit(1)

    for opt, arg in opts:
        if opt in ('-v', '--version'):
            print(g_version.strip())
            sys.exit(0)

        elif opt in ('-o', '--output'):
            if os.path.isdir(arg):
                # we need to ensure that the path ends with a '/'
                if not arg.endswith('/'):
                    arg += '/'
                g_opt['output'] = arg + g_name

            else:
                if os.path.basename(arg) != g_name:
                    print(f'{__file__}: invalid path: {arg}')
                    sys.exit(1)
                g_opt['output'] = arg

        elif opt in ('-h', '--help'):
            print('help')
            sys.exit(0)


# ==========================
# SECTION: xml parser - type
# ==========================

class glType:
    name: str
    value: str
    requires: str

    def __eq__(self, o):
        return (self.name == o.name)


def gl_parsexml_t(element: ET.Element) -> glType:
    type: glType

    type = glType()
    type.name = element.get('name')
    type.requires = element.get('requires')
    if element.text:
        type.value = element.text
    else:
        type.value = str()
    for child in element:
        if child.tag == 'name':
            type.name = child.text
            type.value += type.name
            type.value += child.tail
        if child.tag == 'apientry':
            type.value += 'APIENTRY'
            type.value += child.tail
    return (type)


# ==========================
# SECTION: xml parser - enum
# ==========================

class glEnum:
    name: str
    value: str
    group: str

    def __eq__(self, o):
        return (self.name == o.name)


def gl_parsexml_e(element: ET.Element) -> glEnum:
    enum: glEnum

    enum = glEnum()
    enum.name = element.get('name')
    enum.value = element.get('value')
    enum.group = element.get('group')
    return (enum)


# =============================
# SECTION: xml parser - command
# =============================

class glCmdParam:
    name: str
    ptype: str
    group: str
    cls: str
    len: str


class glCmdProto:
    name: str
    ptype: str


class glCmd:
    name: str
    alias: str
    proto: glCmdProto
    params: list[glCmdParam]

    def __eq__(self, o):
        return (self.name == o.name)


def gl_parsexml_c(element: ET.Element) -> glCmd:
    cmd: glCmd

    cmd = glCmd()
    cmd.params = list()
    for child in element:
        if child.tag == 'proto':
            cmd.proto = gl_parsexml_cproto(child)
            cmd.name = child.find('name').text
        elif child.tag == 'param':
            cmd.params.append(gl_parsexml_cparam(child))
        elif child.tag == 'alias':
            cmd.alias = child.get('name')
    return (cmd)


def gl_parsexml_cproto(element: ET.Element) -> glCmdProto:
    proto: glCmdProto

    proto = glCmdProto()
    proto.ptype = str()
    proto.name = str()

    if element.text:
        proto.ptype += element.text.strip()

    for child in element:
        if child.tag == 'ptype':
            if proto.ptype:
                proto.ptype += ' '
            proto.ptype += f'{child.text.strip()}'.rstrip()
            if child.tail.strip():
                proto.ptype += f' {child.tail.strip()}'.rstrip()

        elif child.tag == 'name':
            proto.name += child.text

    if len(proto.ptype) == 0:
        proto.ptype = f'{element.text.strip()}'
        if element.tail.strip():
            proto.ptype += f'{element.tail.strip()}'.rstrip()
    return (proto)


def gl_parsexml_cparam(element: ET.Element) -> glCmdParam:
    param: glCmdParam

    param = glCmdParam()
    param.name = str()
    param.ptype = str()
    param.group = element.get('group')
    param.cls = element.get('class')
    param.len = element.get('len')

    if element.text:
        param.ptype += element.text
    for child in element:
        if child.tag == 'ptype':
            param.ptype += f'{child.text.strip()} {child.tail.strip()}'.strip()
        elif child.tag == 'name':
            param.name += child.text
    if len(param.ptype) == 0:
        param.ptype = f'{element.text.strip()} {element.tail.strip()}'.strip()
    return (param)


# =============================
# SECTION: xml parser - require
# =============================

class glReq:
    types: list[str]
    enums: list[str]
    cmds: list[str]


def gl_parsexml_r(element: ET.Element) -> glReq:
    req: glReq

    req = glReq()
    req.types = list()
    req.enums = list()
    req.cmds = list()
    for child in element:
        if child.tag == 'type':
            req.types.append(child.get('name'))
        elif child.tag == 'enum':
            req.enums.append(child.get('name'))
        elif child.tag == 'command':
            req.cmds.append(child.get('name'))
    return (req)


# =============================
# SECTION: xml parser - feature
# =============================

class glFeat:
    api: str
    name: str
    number: str
    req: list[glReq]


def gl_parsexml_f(element: ET.Element) -> glFeat:
    feat: glFeat

    feat = glFeat()
    feat.api = element.get('api')
    feat.name = element.get('name')
    feat.number = element.get('number')
    feat.req = list()
    for child in element.findall('require'):
        feat.req.append(gl_parsexml_r(child))
    return (feat)


# ===================
# SECTION: xml parser
# ===================

class glParse:
    types: list[glType]
    enums: list[glEnum]
    cmds: list[glCmd]
    feat: list[glFeat]


def gl_loadxml(filepath: str) -> ET.ElementTree:
    tree: ET.ElementTree

    try:
        tree = ET.parse(filepath)
    except FileNotFoundError as err:
        print(f'{__file__}: {err}')
        sys.exit(1)
    return (tree)


def gl_parsexml(tree: ET.ElementTree) -> glParse:
    root: ET.ElementTree
    parse: glParse

    root = tree.getroot()
    if root.tag != 'registry':
        print(f'{__file__}: root error')
        sys.exit(1)
    parse = glParse()
    parse.types = list()
    parse.enums = list()
    parse.cmds = list()
    parse.feat = list()

    for child in root:

        if child.tag == 'types':
            for types in child.findall('type'):
                type: glType

                type = gl_parsexml_t(types)
                if type not in parse.types:
                    parse.types.append(type)

        elif child.tag == 'enums':
            for enums in child.findall('enum'):
                enum: glEnum

                enum = gl_parsexml_e(enums)
                if enum not in parse.enums:
                    parse.enums.append(enum)

        elif child.tag == 'commands':
            for cmds in child.findall('command'):
                cmd: glCmd

                cmd = gl_parsexml_c(cmds)
                if cmd not in parse.cmds:
                    parse.cmds.append(cmd)

        elif child.tag == 'feature':
            parse.feat.append(gl_parsexml_f(child))

    return (parse)


# ===============
# SECTION: loader
# ===============

def opengl_loader(parse: glParse):
    fstr: str

    with open(g_opt['template'], 'r') as f:
        fstr = f.read()

    fstr = fstr.replace('<<gload-version>>', g_version)
    fstr = fstr.replace('<<gload-author>>', g_author)
    fstr = fstr.replace('<<gload-licence>>', g_licence)
    fstr = fstr.replace('<<gload-version-macro>>', template_version_macro(parse).replace('#', '# '))
    fstr = fstr.replace('<<gload-typedef>>', template_typedefs(parse).replace('#', '# '))
    fstr = fstr.replace('<<gload-enums>>', template_enums(parse).replace('#', '# '))
    fstr = fstr.replace('<<gload-funcptr>>', template_funcptr(parse).replace('#', '# '))
    fstr = fstr.replace('<<gload-loadfunc>>', template_loadfunc(parse).replace('#', '#  '))
    fstr = fstr.replace('<<gload-declr-1>>', template_declr(parse, 1).replace('#', '# '))
    fstr = fstr.replace('<<gload-declr-2>>', template_declr(parse, 2).replace('#', '# '))
    fstr = fstr.replace('<<gload-declr-0>>', template_declr(parse, 0).replace('#', '#  '))

    with open(g_opt['output'], 'w') as f:
        f.write(fstr)


# =================
# SECTION: template
# =================

def template_version_macro(parse: glParse) -> str:
    result: str

    result = str()
    for feat in parse.feat:
        result += f'# define {feat.name} 1\n'
    return (result.strip())


def template_typedefs(parse: glParse) -> str:
    result: str

    result = str()
    for type in parse.types:
        result += f'{type.value}\n'

        # case: #ifdef __APPLE__ ... #endif
        if '__APPLE__' in type.value:
            result = result \
                .replace('#ifdef __APPLE__', '\n#if defined (__APPLE__)\n') \
                .replace('#else', '\n#else\n') \
                .replace('#endif', '\n#endif /* __APPLE__ */\n')
    return (result.strip())


def template_funcptr(parse: glParse) -> str:
    result: str

    result = str()
    for feat in parse.feat:
        result += f'#if defined {feat.name}\n\n'

        for req in feat.req:
            for c_str in req.cmds:
                cmd: glCmd
                func: str

                cmd = next(cmd for cmd in parse.cmds if cmd.name == c_str)
                func = f'typedef {cmd.proto.ptype}'
                func += f' (APIENTRYP PFN{cmd.name.upper()}PROC) ('
                for param in cmd.params:
                    func += f'{param.ptype}, '
                if func[-2:] == ', ':
                    func = func[:-2]
                else:
                    func += 'void'
                func += ');\n'
                result += func
        result += f'\n#endif /* {feat.name} */\n'
    return (result.strip())


def template_enums(parse: glParse) -> str:
    result: str

    result = str()
    for feat in parse.feat:
        result += f'#if defined {feat.name}\n#\n'

        for req in feat.req:
            for e_str in req.enums:
                enum: glEnum

                enum = next(enum for enum in parse.enums if enum.name == e_str)
                result += f'# define {enum.name} {enum.value}\n'

        result += f'#\n#endif /* {feat.name} */\n'
    return (result.strip())


def template_declr(parse: glParse, mode: int) -> str:
    result: str

    result = str()
    for feat in parse.feat:
        result += f'#if defined {feat.name}\n\n'
        # strip the last newline if we print macros...
        if mode == 2:
            result = result[:-1]

        for req in feat.req:
            for c_str in req.cmds:
                cmd: glCmd
                func: str

                cmd = next(cmd for cmd in parse.cmds if cmd.name == c_str)

                if mode == 0:
                    func = f'PFN{cmd.name.upper()}PROC '
                    func += f'gload_{cmd.name};\n'
                    if result.find(func) != -1:
                        result += 'extern '
                    result += func

                elif mode == 1:
                    func = 'extern '
                    func += f'PFN{cmd.name.upper()}PROC '
                    func += f'gload_{cmd.name};\n'
                    result += func

                elif mode == 2:
                    func = '# define '
                    func += f'{cmd.name} '
                    func += f'gload_{cmd.name}\n'
                    result += func

        # add a newline if we're not printing macros...
        if mode != 2:
            result += '\n'
        result += f'#endif /* {feat.name} */\n'
    return (result.strip())


def template_loadfunc(parse: glParse) -> str:
    result: str

    result = str()
    for feat in parse.feat:
        result += f'#if defined {feat.name}\n\n'

        for req in feat.req:
            for c_str in req.cmds:
                cmd: glCmd
                name: str

                cmd = next(cmd for cmd in parse.cmds if cmd.name == c_str)
                name = f'   if (!gload_{cmd.name} && '
                name += f'!(gload_{cmd.name} = '
                name += f'(PFN{cmd.name.upper()}PROC) load(\"{cmd.name}\"))) '
                name += '{ return (0); }\n'
                result += name
        result += f'\n#endif /* {feat.name} */\n'
    return (result.strip())


# =============
# SECTION: main
# =============

if __name__ == '__main__':
    gl_getopt()

    try:
        tree = gl_loadxml(f'{g_path}/xml/gl.xml')
        parse = gl_parsexml(tree)
        opengl_loader(parse)
    except Exception as err:
        print(f'{__file__}: {err}')
        sys.exit(1)
