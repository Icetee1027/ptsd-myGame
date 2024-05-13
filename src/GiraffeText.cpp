#include "GiraffeText.hpp"

#include "SynthesisTable.hpp"
#include <map>
#include "Util/Time.hpp"


void GiraffeText::Start() {
   
}
void GiraffeText::InitText(std::string path, int t,std::string str, glm::vec3 c) {
    m_Moveable = true;
    m_Drawable = std::make_shared<Util::Text>(path, t, str,
        Util::Color::FromRGB(c.x, c.y, c.z));

    m_Drawable->SetWorld(Core::Drawable::World::UI);
    m_Visible = true;
}
void GiraffeText::Update() {

}
void GiraffeText::ClickDown() {
  
}
void GiraffeText::ClickUp() {

}
void GiraffeText::BluePrintINIT() {
    for (int i = 1; i < 35; i++) {
        ShowBluePrint.push_back(std::to_string(i) + ". ");
    }
    std::string t_str = "";
    for (auto& text : ShowBluePrint) {
        t_str += text + "\n";
    }
    SetText(t_str);
}
void GiraffeText::AddBluePrint(std::string str) {
    for (auto& t : ShowBluePrint) {
        if (t.size() < 5) {
            std::string substr = str.substr(5); 
            if (substr == "Offspring") {
                substr = "Villager";
            }
            else if (substr == "Growth") {
                t += "Growth=Plant+Planting";
                break;
            }
            for (auto& s : SynthesisTable::m_SynthesisTable) {
                if (str.length() >= 5) {
                    if (substr == s.name ) {
                        t += s.name + "=";
                        std::map<std::string, int> countMap;
                        for (const auto& str : s.need) {
                            countMap[str]++;
                        }
                        
                        int count = 0;
                        for (const auto& pair : countMap) {
                            if (count == 2) {
                                t += "\n    ";
                                count = 0; // 重置计数器
                            }
                            t += pair.first + "*" + std::to_string(pair.second);
                            count++;
                            // 每添加三个字符串后插入换行符
                            t += "+";
                        }
                        if (!t.empty()) {
                            t.pop_back();
                        }
                        break;
                    }
                }
            }
            break;
        }
    }
    std::string t_str = "";
    for (auto& text : ShowBluePrint) {
        t_str += text + "\n";
    }
    SetText(t_str);
    m_Transform.translation.x = GetScaledSize().x / 2 - 635;
    m_Transform.translation.y = GetScaledSize().y / 2 - 358;

}
