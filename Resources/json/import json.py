import json

def create_custom_json(filename, data):
    try:
        with open(filename, 'w') as file:
            json.dump(data, file, indent=4)
        print(f"JSON 檔案 '{filename}' 創建成功！")
    except Exception as e:
        print(f"創建 JSON 檔案時發生錯誤：{e}")

def main():
    while 1:
        
        filename = input("請輸入要創建的 JSON 檔案名稱（包含檔案擴展名）：")
        data = {}
        data['name'] = filename
        if not filename.endswith('.json'):
            filename += '.json'
    
        # 自訂義輸入數據，這只是一個示例，您可以根據需要修改
        data['id'] = 0
        data['class'] = "Resource"
        data['type'] = 5
       
        
        data['price'] = int(input("Price:"))
        #if input("是否輸入 satiety？(y/n): ").lower() == 'y':
        #data['satiety'] = int(input("satiety:"))
        #if input("是否輸入 hp？(y/n): ").lower() == 'y':
        #data['hp'] = int(input("hp"))
    
        create_custom_json(filename, data)

if __name__ == "__main__":
    main()
