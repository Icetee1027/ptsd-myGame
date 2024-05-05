#ifndef SYNRTHESISTABLE_HPP
#define SYNRTHESISTABLE_HPP
#include "pch.hpp"
#include <set>
#include "Card/AllCardPch.hpp"
#include <typeindex>
class SynthesisTable {
public:
    
    struct Table {
        std::string name;
        std::vector<std::string> need;
        std::vector<std::string> delet;
        float time;
        bool random;
        std::string medium;
        int mediumInt=1;
        Table(const std::string& n, const std::vector<std::string>& n_, const std::vector<std::string>& d, float t, bool r,std::string m="", int i = 1)
            : name(n), need(n_), delet(d), time(t), random(r),medium(m),mediumInt(i){}
    };

    static std::vector<Table> m_SynthesisTable;

    static std::pair<int, int> SyntheticCheck(std::vector<std::string> &cards);
};


#endif // !SYNRTHESISTABLE_HPP
