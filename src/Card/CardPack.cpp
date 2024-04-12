#include "Card/CardPack.hpp"
#include "Card/Card.hpp"
#include "Card/CardMaker.hpp"
#include <cstddef>
#include <glm/fwd.hpp>
#include <memory>
#include "App.hpp"
#include "Mouse.hpp"
#include "Util/Logger.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
namespace card {
    CardPack::CardPack(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image,  const bool iconcolor)
        : Card(type, name, id, sfxs, image, iconcolor){
    }

    void CardPack::GenerateCard(){
        if(num < this->GetCardPackNum()){
            std::shared_ptr<Card> tmp;
            tmp = CardMaker::MakeCard(DrawCard(num));
            tmp->SetTranslation(glm::vec3(this->GetTransform().translation.x, this->GetTransform().translation.y + 200, 0));
            App::AddCard(tmp);
            num++;
            LOG_DEBUG("Num:{}", num);
        }
    }

    std::string CardPack::DrawCard(unsigned short num){
        std::string CardName;
        if(num == 0){
            std::vector<std::string> tmp = this->GetFirstIdeaPool();
            size_t len = tmp.size();
            if(len != 0){
                //FirstIdeaChoose
                int randomNumber = rand() % len;
                LOG_DEBUG("randomNumber:{}", randomNumber);
                CardName = tmp[randomNumber];
                LOG_DEBUG("CardName:{}",CardName);
                tmp.erase(tmp.begin() + randomNumber);
                this->SetFirstIdeaPool(tmp);
            }
            else{
                //FirstCardsChoose
                unsigned short index = 0;
                unsigned short totalRate = this->GetFirstCardsRate()[index];
                tmp = this->GetFirstCardsPool();
                len = tmp.size();
                int randomNumber = rand() % 99 + 1;
                LOG_DEBUG("randomNumber:{}", randomNumber);
                while(1){
                    if (randomNumber <= totalRate) {
                        CardName = tmp[index];
                        break;
                    }
                    totalRate += this->m_FirstCardsRate[++index];
                }
                LOG_DEBUG("CardName:{}",CardName);
            }
        }
        else if(num == 1){
            std::vector<std::string> tmp = this->GetSecondIdeaPool();
            size_t len = tmp.size();
            if(len != 0){
                //SecondIdeaChoose
                int randomNumber = rand() % len;
                LOG_DEBUG("randomNumber:{}", randomNumber);
                CardName = tmp[randomNumber];
                LOG_DEBUG("CardName:{}",CardName);
                tmp.erase(tmp.begin() + randomNumber);
                this->SetSecondIdeaPool(tmp);
            }
            else{
                //SecondCardsChoose
                tmp = this->GetSecondCardsPool();
                len = tmp.size();
                int randomNumber = rand() % len;
                LOG_DEBUG("randomNumber:{}", randomNumber);
                CardName = tmp[randomNumber];
                LOG_DEBUG("CardName:{}",CardName);
            }
        }
        else if(num == 2){
            std::vector<std::string> tmp = this->GetThirdIdeaPool();
            size_t len = tmp.size();
            if(len != 0){
                //ThirdIdeaChoose
                int randomNumber = rand() % len;
                LOG_DEBUG("randomNumber:{}", randomNumber);
                CardName = tmp[randomNumber];
                LOG_DEBUG("CardName:{}",CardName);
                tmp.erase(tmp.begin() + randomNumber);
                this->SetThirdIdeaPool(tmp);
            }
            else{
                //ThirdCardsChoose
                tmp = this->GetThirdCardsPool();
                len = tmp.size();
                int randomNumber = rand() % len;
                LOG_DEBUG("randomNumber:{}", randomNumber);
                CardName = tmp[randomNumber];
                LOG_DEBUG("CardName:{}",CardName);
            }
        }
        else{
            std::vector<std::string> tmp = this->GetForthIdeaPool();
            size_t len = tmp.size();
            if(len != 0){
                //ForthIdeaChoose
                int randomNumber = rand() % len;
                LOG_DEBUG("randomNumber:{}", randomNumber);
                CardName = tmp[randomNumber];
                LOG_DEBUG("CardName:{}",CardName);
                tmp.erase(tmp.begin() + randomNumber);
                this->SetForthIdeaPool(tmp);
            }
            else{
                //ForthCardsChoose
                tmp = this->GetForthCardsPool();
                len = tmp.size();
                int randomNumber = rand() % len;
                LOG_DEBUG("randomNumber:{}", randomNumber);
                CardName = tmp[randomNumber];
                LOG_DEBUG("CardName:{}",CardName);
            }
        }
        return CardName;
    }

    void CardPack::ClickDown(){
        GenerateCard();
    }

    void CardPack::ClickUp(){
        //LOG_DEBUG("CardPack_test");
    }
}