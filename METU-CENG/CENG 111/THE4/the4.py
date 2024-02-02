
def inheritance(Descriptions):
    res = []
    def depth(lst):
        depths = []
        for i in lst:
            if isinstance(i, list):
                depths.append(depth(i))
        if len(depths) > 0:
            return 1 + max(depths)
        return 1

    def dict_des(Descriptions):
        des_list = []
        for i in range(len(Descriptions)):
            des_list.append(Descriptions[i].split())
        family = {'child': [], 'departed': [], 'married': []}
        for i in range(len(des_list)):
            if des_list[i][0] == 'CHILD':
                for j in range(3, len(des_list[i])):
                    family['child'].append(des_list[i][j])
            elif des_list[i][0] == 'DEPARTED':
                family['departed'].append(des_list[i][1])
            elif des_list[i][0] == 'MARRIED':
                family['married'].append((des_list[i][1], des_list[i][2]))
        return family, des_list

    des_list = dict_des(Descriptions)[1]
    fam = dict_des(Descriptions)[0]

    def return_elm_depth(lst):
        ans = {}
        for i in range(depth(lst)):
            for j in range(len(lst)):
                if isinstance(lst[j], list):
                    for k in range(len(lst[j])):
                        lst.append(lst[j][k])
                elif not isinstance(lst[j], list) and lst[j] not in ans.keys():
                    ans[lst[j]] = i + 1
        return ans

    def deceased(des_list):
        for i in range(len(des_list)):
            if des_list[i][0] == 'DECEASED':
                return des_list[i][1]

    def heritage_value(des_list):
        for i in range(len(des_list)):
            if des_list[i][0] == 'DECEASED':
                return int(des_list[i][2])

    def is_married(target):
        for i in range(len(des_list)):
            if des_list[i][0] == 'MARRIED':
                if des_list[i][1] == target:
                    return True
                elif des_list[i][2] == target:
                    return True
        return False

    def find_spouse(target):
        for i in range(len(des_list)):
            if des_list[i][0] == 'MARRIED':
                if des_list[i][1] == target:
                    return des_list[i][2]
                elif des_list[i][2] == target:
                    return des_list[i][1]

    def alive_offspring(target):
        alive_off = []
        for i in range(len(des_list)):
            if des_list[i][0] == 'CHILD':
                if des_list[i][1] == target or des_list[i][2] == target:
                    for j in range(3, len(des_list[i])):
                        if des_list[i][j] not in fam['departed']:
                            alive_off.append(des_list[i][j])
                        else:
                            z = alive_offspring(des_list[i][j])
                            alive_off.append(z)
        return alive_off

    def is_spouse_alive(target):
        spouse = ''
        for i in range(len(des_list)):
            if des_list[i][0] == 'MARRIED':
                if target == des_list[i][1]:
                    spouse = des_list[i][2]
                elif target == des_list[i][2]:
                    spouse = des_list[i][1]
        if spouse not in fam['departed']:
            return True
        return False

    def pg1(target):
        PG1 = []
        PG1.extend(alive_offspring(target))
        return PG1

    def pg2(target):
        PG2 = []
        for i in range(len(des_list)):
            if des_list[i][0] == 'CHILD' and target in des_list[i][3:]:
                PG2.append(des_list[i][1])
                PG2.append(des_list[i][2])
        for i in range(len(PG2)):
            if PG2[i] in fam['departed']:
                PG2[i] = pg1(PG2[i])
        return PG2

    def pg3(target):
        PG3 = []
        p1 = ''
        p2 = ''
        for i in range(len(des_list)):
            if des_list[i][0] == 'CHILD' and target in des_list[i][3:]:
                p1 = des_list[i][1]
                p2 = des_list[i][2]
        pg2p1 = pg2(p1)
        pg2p2 = pg2(p2)
        PG3.append(pg2p1)
        PG3.append(pg2p2)
        return PG3

    target = deceased(des_list)
    spouse = find_spouse(target)
    heritage = heritage_value(des_list)
    PG1 = return_elm_depth(pg1(deceased(des_list)))
    keys = list(PG1.keys())
    vals = list(PG1.values())
    if PG1:
        if is_married(target) and is_spouse_alive(target):
            res.append((spouse, heritage / 4))
            if vals.count(1) == 1:
                herit = (heritage - (heritage / 4)) / len(set(vals))
                for i in range(len(PG1)):
                    if vals[i] == 1:
                        res.append((keys[i], (heritage - (heritage / 4)) / len(vals)))
                    elif vals.count(vals[i]) == 1 and vals[i] != 1:
                        res.append((keys[i], herit))
                    else:
                        res.append((keys[i], herit / vals.count(vals[i])))
            elif len(set(vals)) == 1 and vals.count(1) != 1:
                herit = (heritage - (heritage / 4)) / len(vals)
                for i in range(len(PG1)):
                    res.append((keys[i], herit))
            else:
                herit = (heritage - (heritage / 4)) / (len(vals) - vals.count(1) + 1)
                for i in range(len(PG1)):
                    if vals[i] == 1:
                        res.append((keys[i], herit))
                    elif vals.count(vals[i]) == 1 and vals[i] != 1:
                        res.append((keys[i], herit))
                    else:
                        res.append((keys[i], herit / vals.count(vals[i])))
        else:
            herit = heritage / len(set(vals))
            for i in range(len(PG1)):
                if vals.count(vals[i]) == 1:
                    res.append((keys[i], herit))
                else:
                    res.append((keys[i], herit / vals.count(vals[i])))
        ss = 0
        for i in range(len(res)):
            ss += res[i][1]
        oo = heritage - ss
        if oo != 0:
            temp = res[-1]
            t1 = temp[0]
            t2 = temp[1]
            t2 += oo
            del res[-1]
            res.append((t1, t2))
        return res
    PG2 = return_elm_depth(pg2(target))
    keys = list(PG2.keys())
    vals = list(PG2.values())
    if PG2 and not PG1:
        if is_married(target) and is_spouse_alive(target):
            res.append((spouse, heritage / 2))
            herit = (heritage - (heritage / 2))
            for i in range(len(PG2)):
                res.append((keys[i], herit / (2 ** vals[i])))
            ss = 0
            for i in range(len(res)):
                ss += res[i][1]
            oo = heritage - ss
            if oo != 0:
                temp = res[-1]
                t1 = temp[0]
                t2 = temp[1]
                t2 += oo
                del res[-1]
                res.append((t1, t2))
            return res
        else:
            if vals.count(1) == 1:
                herit = heritage / 2
                for i in range(len(PG2)):
                    if vals[i] == 1:
                        res.append((keys[i], herit))
                    elif vals[i] != 1 and vals.count(vals[i]) == 1:
                        res.append((keys[i], herit))
                    else:
                        res.append((keys[i], herit / vals.count(vals[i])))
            else:
                if len(set(vals)) == 1 and vals.count(1) != 0:
                    herit = heritage / vals.count(1)
                    for i in range(len(PG2)):
                        if vals[i] == 1:
                            res.append((keys[i],herit))
                        else:
                            res.append((keys[i],herit/vals.count(vals[i])))
                else:
                    herit = heritage / (vals.count(1) + 1)
                    for i in range(len(PG2)):
                        if vals[i] == 1:
                            res.append((keys[i], herit))
                        else:
                            res.append((keys[i], herit / vals.count(vals[i])))
            ss = 0
            for i in range(len(res)):
                ss += res[i][1]
            oo = heritage - ss
            if oo != 0 and res:
                temp = res[-1]
                t1 = temp[0]
                t2 = temp[1]
                t2 += oo
                del res[-1]
                res.append((t1, t2))
            return res
    PG3 = return_elm_depth(pg3(target))
    keys = list(PG3.keys())
    vals = list(PG3.values())
    if PG3 and not PG1 and not PG2:
        if is_married(target) and is_spouse_alive(target):
            res.append((spouse, 3 * heritage / 4))
            herit = (heritage - (3 * heritage / 4))
            for i in range(len(PG3)):
                res.append((keys[i], herit / len(vals)))
            ss = 0
            for i in range(len(res)):
                ss += res[i][1]
            oo = heritage - ss
            if oo != 0:
                temp = res[-1]
                t1 = temp[0]
                t2 = temp[1]
                t2 += oo
                del res[-1]
                res.append((t1, t2))
            return res
        else:
            for i in range(len(PG3)):
                res.append((keys[i], heritage / (2 ** vals[i])))
            ss = 0
            for i in range(len(res)):
                ss += res[i][1]
            oo = heritage - ss
            if oo != 0:
                temp = res[-1]
                t1 = temp[0]
                t2 = temp[1]
                t2 += oo
                del res[-1]
                res.append((t1, t2))
            return res
    if not PG3 and not PG1 and not PG2:
        if is_married(target) and is_spouse_alive(target):
            res.append((spouse, heritage))
            return res
        else:
            return res
