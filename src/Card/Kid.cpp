#include "Card/Kid.hpp"
#include "SystemSettlementUI.hpp"
namespace card {
    Kid::Kid(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    void Kid::UpdateCard() {
        if (SystemSettlementUI::IsSystemUpdta) {
            SystemSettlementUI::AmountFoodRequired += 1;
            SystemSettlementUI::CurrentStorageCapacity++;
        }
    }
    void Kid::VillagerDead() {
        GenerateCard(std::string("Corpse"));
    }
}