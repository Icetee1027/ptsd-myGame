#ifndef BONE_HPP
#define BONE_HPP
#include "pch.hpp"
#include "Card/Resource.hpp"
namespace card {
	class Bone :public Resource {
	private:
	public:
		Bone(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Bone() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
	};
}
#endif // !BONE_HPP
