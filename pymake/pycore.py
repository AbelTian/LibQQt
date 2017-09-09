# -*- coding: utf-8 -*-
import os
import sys
import traceback
import ConfigParser
import json


class PyConfig(ConfigParser.ConfigParser):
    def __init__(self,defaults=None):
        ConfigParser.ConfigParser.__init__(self,defaults=None)
    def optionxform(self, optionstr):
        return optionstr


class PyCMakeConfig():
    def __init__(self,defaults=None):
        ""

    def readSet(self, file, key):
        getSet = ""
        with open(file, "r") as f:
            target = 0
            for line in f.readlines():

                line = line.strip()
                line = line.strip('\"')
                line = line.strip('\r')
                line = line.strip('\n')
                line = line.replace('\"', '')
                line = line.replace('\'', '')
                line = line.replace('\\', os.sep)
                line = line.replace('/', os.sep)

                if ( line.find('#') >= 0
                     or len(line) <= 0 ):
                    continue

                if (line.find("set") >= 0 & line.find("(") >= 0):
                    target = 1

                elif (line.find(")") >= 0):
                    target = 0
                    if(getSet.find(key) >= 0):
                        break
                    getSet = ""

                if(target == 1):
                    if ( line.find('set') >= 0 & line.find('(') >= 0 ) :
                        continue

                    getSet += line + ','

        getSet = filter(lambda x: len(x.strip()) > 0, getSet.split(','))

        return getSet

    def readPymakeSet(self, file):
        getSet = ""
        dict_value = {}
        dict_group = {}
        dict_target = {}
        with open(file, "r") as f:
            target = 0
            groupName = ""
            groupID = 0
            key = ""
            value = ""
            for line in f.readlines():

                line = line.strip()
                line = line.strip('\r')
                line = line.strip('\n')
                line = line.replace('\"', '')
                line = line.replace('\'', '')
                line = line.replace('\\', os.sep)
                line = line.replace('/', os.sep)

                if ( line.find('#') >= 0
                     or len(line) <= 0 ):
                    continue

                #print target, line

                #target = 1 'set' topest
                elif (line.find('set') >= 0 & line.find('(') >= 0):
                    target = 1

                #target = 0 topest
                elif (line.find(')') >= 0):
                    target = 0
                    dict_group = {}
                    dict_value = {}
                    groupID = 0
                    continue

                #target = 2 '[' second level
                elif (line.find("[") >= 0):
                    target = 2

                elif (line.find(']') >= 0):
                    # pop level
                    target = 1
                    dict_value = {}
                    continue



                if(target == 1):
                    if (line.find('set') >= 0 & line.find('(') >= 0 ) :
                        groupName = line.split('[')[1].split(']')[0].strip()

                        dict_group = {}
                        dict_value = {}
                        groupID = 0

                        continue

                    if(line == '*' or line == '-'):

                        dict_value['PYMAKE_BUILD'] = line
                        dict_group[groupID] = dict_value
                        dict_target[groupName] = dict_group

                    elif( line.find('=') >= 0 ):

                        key = line.split('=')[0].strip()
                        value = line.split('=')[1].strip()

                        dict_value[key] = value
                        dict_group[groupID] = dict_value
                        dict_target[groupName] = dict_group



                elif(target == 2):
                    if ( line.find('[') >= 0 ):
                        groupID += 1
                        dict_value = {}

                    if(line == '*' or line == '-'):

                        dict_value['PYMAKE_BUILD'] = line
                        dict_group[groupID] = dict_value
                        dict_target[groupName] = dict_group

                    elif(line.find('=') >= 0):

                        key = line.split('=')[0].strip()
                        value = line.split('=')[1].strip()

                        dict_value[key] = value
                        dict_group[groupID] = dict_value
                        dict_target[groupName] = dict_group

        return dict_target


def readJsonData(file):

    datas = ""
    with open(file, 'r') as json_file:
        for line in json_file.readlines():
            datas += line

    data = json.loads(datas, encoding='utf-8')
    return data

def writeJsonData(file, data):
    with open(file, 'w') as json_file:
        #json_file.write(json.dumps(data, sort_keys=False, indent=4, separators=(',', ' = '), ensure_ascii = False))
        json_file.write(json.dumps(data, sort_keys=False, indent=4))

def processJson(inputJsonFile, outputJsonFile):
    fin = open(inputJsonFile, 'r')
    fout = open(outputJsonFile, 'w')
    for eachLine in fin:
        line = eachLine.strip().decode('utf-8')  # 去除每行首位可能的空格，并且转为Unicode进行处理
        line = line.strip(',')  # 去除Json文件每行大括号后的逗号
        js = None
        try:
            js = json.loads(line)  # 加载Json文件
        except Exception, e:
            print 'bad line'
            continue
        js["xxx"] = ''  # 对您需要修改的项进行修改，xxx表示你要修改的内容
        outStr = json.dumps(js, ensure_ascii=False) + ','  # 处理完之后重新转为Json格式，并在行尾加上一个逗号
        fout.write(outStr.strip().encode('utf-8') + '\n')  # 写回到一个新的Json文件中去
    fin.close()  # 关闭文件
    fout.close()


def object2dict(obj):
    # convert object to a dict
    d = {}
    d['__class__'] = obj.__class__.__name__
    d['__module__'] = obj.__module__
    d.update(obj.__dict__)
    return d


def dict2object(d):
    # convert dict to object
    if '__class__' in d:
        class_name = d.pop('__class__')
        module_name = d.pop('__module__')
        module = __import__(module_name)
        class_ = getattr(module, class_name)
        args = dict((key.encode('ascii'), value) for key, value in d.items())  # get args
        inst = class_(**args)  # create new instance
    else:
        inst = d
    return inst


class PyJsonEncoder(json.JSONEncoder):
    def default(self, obj):
        # convert object to a dict
        d = {}
        d['__class__'] = obj.__class__.__name__
        d['__module__'] = obj.__module__
        d.update(obj.__dict__)
        return d


class PyJsonDecoder(json.JSONDecoder):
    def __init__(self):
        json.JSONDecoder.__init__(self, object_hook=self.dict2object)

    def dict2object(self, d):
        # convert dict to object
        if '__class__' in d:
            class_name = d.pop('__class__')
            module_name = d.pop('__module__')
            module = __import__(module_name)
            class_ = getattr(module, class_name)
            args = dict((key.encode('utf-8'), value) for key, value in d.items())  # get args
            inst = class_(**args)  # create new instance
        else:
            inst = d
        return inst
