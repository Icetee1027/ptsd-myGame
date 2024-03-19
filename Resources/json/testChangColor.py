import os
import json

# 匹配的字符串列表
match_strings = [
    "Bone",
    "Flint",
    "MagicDust",
    "Wood",
    "Brick",
    "Stick",
    "Stone",
    "IronBar",
    "IronOre",
    "OldTome",
    "Plank",
    "Soil",
    "IronDeposit",
    "Tree",
    "AppleTree",
    "BerryTree",
    "Rock",
    "Map",
    "Sword",
    "Spear",
    "RumorCombat",
    "RumorDarkForest",
    "Idea",
    "Rabbit",
    "Chicken",
    "Cow",
    "Catacombs",
    "Forest",
    "Graveyard",
    "Mountain",
    "OldVillage",
    "Plains"
]

# 获取当前目录
current_directory = os.getcwd()

# 遍历目录中的所有文件
for filename in os.listdir(current_directory):
    if filename.endswith('.json'):
        # 构建文件路径
        filepath = os.path.join(current_directory, filename)
        
        # 读取JSON文件
        with open(filepath, 'r') as file:
            data = json.load(file)
        
        # 判断name字段是否在匹配的字符串列表中，如果是则texticon设置为1，否则设置为0
        if data.get('name') in match_strings:
            data['textcolor'] = 1
        else:
            data['textcolor'] = 0
        
        # 写回JSON文件
        with open(filepath, 'w') as file:
            json.dump(data, file, indent=4)

print("操作完成：已根据匹配的字符串列表生成了相应的texticon字段值。")
