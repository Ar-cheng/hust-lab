def tuple2json(data, args):
    if(len(args)!=len(data)):
        return {};
    dict = {}
    for i, x in enumerate(data):
        dict[args[i]] = x
    return dict

def tupletojson(data,args):
    res = []
    for each in data:
        ret = tuple2json(each,args)
        res.append(ret)
    return res

if __name__ == '__main__':
    test1 =(("2020000000", "朱志成", 21, 0, "技术部", "正式工", 6, 20000),("2020000000", "朱志成", 21, 0, "技术部", "正式工", 6, 20000) )
    dict = ('UID','姓名','年龄','性别','工种','部门','职阶','基础薪资')
    res = tupletojson(test1,dict)
    print(res)