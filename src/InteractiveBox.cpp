#include "InteractiveBox.hpp".
#include "Util/Image.hpp"
#include "Util/Text.hpp"

InteractiveBox::InteractiveBox() {
	m_Drawable=std::make_shared<Util::Image>(RESOURCE_DIR"/sprites/InteractiveBox.png");
	m_Drawable->SetWorld(Core::Drawable::World::UI);
	m_Transform.scale = { 0.5,0.5 };
	m_GiraffeText[0]->InitText(RESOURCE_DIR"/fonts/Inter.ttf", 20, " ", glm::vec3(0, 0, 0));
	m_GiraffeText[1]->InitText(RESOURCE_DIR"/fonts/Inter.ttf", 40, "o", glm::vec3(0, 0, 0));
	m_GiraffeText[0]->SetZIndex(4);
	m_GiraffeText[1]->SetZIndex(4);
	m_vec3s = { glm::vec3(),glm::vec3(0,-60,0) };
    m_ZIndex = 3;
	m_Children.push_back(m_GiraffeText[0]);
	m_Children.push_back(m_GiraffeText[1]);


}
void InteractiveBox::Update() {
	for (int i = 0; i < m_GiraffeText.size();i++) {
		m_GiraffeText[i]->SetMoveable(1);
		m_GiraffeText[i]->SetTranslation(m_Transform.translation+m_vec3s[i]);
		m_GiraffeText[i]->SetMoveable(0);
		m_GiraffeText[i]->Update();
	}
}
void InteractiveBox::SetText(int a, std::string str) {
    if (a != 1 && a != 0) return;

    // 确定文本框的宽度
    float boxWidth = GetScaledSize().x-10;
    std::vector<std::string> words;
    size_t pos = 0, found;
    while ((found = str.find_first_of(' ', pos)) != std::string::npos) {
        words.push_back(str.substr(pos, found - pos));
        pos = found + 1;
    }
    words.push_back(str.substr(pos));  // 添加最后一个单词
    m_GiraffeText[a]->SetText(" ");
    std::string currentLine;
    std::string wrappedText;

    for (const auto& word : words) {
        // 加上当前单词后测试行
        std::string testLine = currentLine.empty() ? word : currentLine + " " + word;
        if (testLine == "")testLine = " ";
        m_GiraffeText[a]->SetText(testLine);

        // 如果测试行的宽度超过了框的宽度，则换行
        if (m_GiraffeText[a]->GetScaledSize().x > boxWidth) {
            if (!currentLine.empty()) {
                if (!wrappedText.empty()) {
                    wrappedText += "\n";
                }
                wrappedText += currentLine;
            }
            currentLine = word;  // 新行的第一个单词
        }
        else {
            currentLine = testLine;  // 加入当前单词后的行
        }
    }

    // 添加最后一行
    if (!currentLine.empty()) {
        if (!wrappedText.empty()) {
            wrappedText += "\n";
        }
        wrappedText += currentLine;
    }

    // 设置分段后的文本
    m_GiraffeText[a]->SetText(wrappedText);
	if (a == 0) {
		m_vec3s[0] = glm::vec3(m_vec3s[0].x, GetScaledSize().y / 2 - 15 - m_GiraffeText[0]->GetScaledSize().y / 2, m_vec3s[0].z);
	}

}
void InteractiveBox::SetVisible( bool visible) {
	m_Visible=visible;
	m_GiraffeText[0]->SetVisible(visible);
	m_GiraffeText[1]->SetVisible(visible);
}
