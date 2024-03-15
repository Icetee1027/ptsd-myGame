import os

def remove_extension(filename):
    """去除文件名中的扩展名"""
    return os.path.splitext(filename)[0]

def list_files_without_extension(directory):
    """获取指定目录中所有文件的名称（不包括扩展名）"""
    files_without_extension = []
    for filename in os.listdir(directory):
        if os.path.isfile(os.path.join(directory, filename)):
            files_without_extension.append(remove_extension(filename))
    return files_without_extension

# 获取当前文件所在目录
directory = os.path.dirname(__file__)

# 获取目录中所有文件的名称（不包括扩展名）
files_without_extension = list_files_without_extension(directory)

# 生成类似于 C++ 中的初始化列表
cpp_vector_style = "{" + ", ".join(f'"{file}"' for file in files_without_extension) + "}"

# 打印结果
print("std::vector<std::string> files = " + cpp_vector_style + ";")
