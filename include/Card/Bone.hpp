#ifndef BONE_HPP
#define BONE_HPP
#include "pch.hpp"
#include "Card/Resource.hpp"
namespace card {
	class Bone :public Resource {
	private:
	public:
		Bone(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~Bone() override = default;
	};
}
#endif // !BONE_HPP
