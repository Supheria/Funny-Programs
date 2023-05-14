// 职业记录格式（未加密）：
//	0		1		2		3				4				5			6				7			8
// CARR|职业编号|职业名称|天赋期望|天赋方差（0为默认2.5）|财富期望|财富方差（0为默认50）|最新天赋值|最新财富值
#include "career.h"
#include "normaldistribution.h"
#include "tools.h"
#include "dir.h"

static std::vector<Career> career;
static struct Ini {
	uint m_carrnum; // 职业的唯一编号
	std::string m_carrname; // 职业名称
	ushrt m_gift; // 天赋期望
	float m_gift_variance; // 天赋方差
	uint m_wealth; // 财富期望
	float m_wlth_variance; // 财富方差
	ushrt m_last_gift; // 最新天赋点数
	uint m_last_wlth; // 最新财富值
}ini[] = {
	{ 0001, "探险者", 15, 1.5, 500, 0, 0, 0 },
	{ 0002, "富二代", 5, 0, 1000, 0, 0, 0 },
	{ 0003, "企业家", 15, 3.5, 2000, 0, 0, 0 },
};
static float DefaultGiftVariance{ 2.5 }, DefaultWlthVariance{ 50 };

bool IniCareer()
{
	using namespace std; using namespace myTools; using namespace ieTools;
	string path = ini_CareerPath();
	if (TestFileExistence(path))
	{
		ifstream fin(path);
		while (fin.peek() != EOF)
		{
			string line;
			getline(fin, line);
			decoder(line);
			auto vLine = SplitString(line, SPLITPATTERN_CARR());
			if (vLine[0] == "CARR")
			{
				Career newcarr;
				newcarr.m_carrnum = atoi(vLine[1].c_str());
				newcarr.m_carrname = vLine[2];
				newcarr.m_gift = atoi(vLine[3].c_str());
				newcarr.m_gift_variance = (atoi(vLine[4].c_str()) ? atoi(vLine[4].c_str()) : DefaultGiftVariance);
				newcarr.m_wealth = atoi(vLine[5].c_str());
				newcarr.m_wlth_variance = (atoi(vLine[6].c_str()) ? atoi(vLine[6].c_str()) : DefaultWlthVariance);
				newcarr.m_last_gift = atoi(vLine[7].c_str());
				newcarr.m_last_wlth = atoi(vLine[8].c_str());
				career.push_back(newcarr);
			}
		}
		if (!career.size())
		{
			for (int i = 0; i < sizeof(ini) / sizeof(*ini); i++)
			{
				Career newcarr;
				newcarr.m_carrnum = ini[i].m_carrnum;
				newcarr.m_carrname = ini[i].m_carrname;
				newcarr.m_gift = ini[i].m_gift;
				newcarr.m_gift_variance = ini[i].m_gift_variance ? ini[i].m_gift_variance : DefaultGiftVariance;
				newcarr.m_wealth = ini[i].m_wealth;
				newcarr.m_wlth_variance = ini[i].m_wlth_variance ? ini[i].m_wlth_variance : DefaultWlthVariance;
				newcarr.m_last_gift = ini[i].m_last_gift;
				newcarr.m_last_wlth = ini[i].m_last_wlth;
				career.push_back(newcarr);
			}
		}
		return true;
	}
	return false;
}
void OutputCareer()
{
	using namespace std; using namespace myTools;
	ofstream fout(ini_CareerPath());
	for (auto it = career.begin(); it != career.end(); it++)
	{
		string line = "CARR" + SPLITPATTERN_CARR() + to_string((*it).m_carrnum) + SPLITPATTERN_CARR() + (*it).m_carrname + SPLITPATTERN_CARR() + to_string((*it).m_gift) + SPLITPATTERN_CARR() + to_string((*it).m_gift_variance) + SPLITPATTERN_CARR() + to_string((*it).m_wealth) + SPLITPATTERN_CARR() + to_string((*it).m_wlth_variance) + SPLITPATTERN_CARR() + to_string((*it).m_last_gift) + SPLITPATTERN_CARR() + to_string((*it).m_last_wlth);
		fout << encoder(line) << endl;
	}
}
uint ShowCareer()
{
	using namespace std;
	for (int i = 0; i < career.size(); i++)
	{
		cout << i + 1 << ". " << career[i].m_carrname << endl;
	}
	return career.size();
}
CarrInfo SelectCareer(uint pos)
{
	Career& pCarr = career[pos - 1];
	pCarr.m_last_gift = pCarr.m_last_gift ? pCarr.m_last_gift : GetANormalDistributionNumber<ushrt>(pCarr.m_gift, pCarr.m_gift_variance);
	pCarr.m_last_wlth = pCarr.m_last_wlth ? pCarr.m_last_wlth : GetANormalDistributionNumber<uint>(pCarr.m_wealth, pCarr.m_wlth_variance);
	struct CarrInfo carrinfo {
		pCarr.m_carrnum,
			pCarr.m_last_gift,
			pCarr.m_last_wlth,
			pCarr.m_carrname
	};
	return carrinfo;
}
void UpdateSelectedCareer(CarrInfo& carrinfo)
{
	using namespace std;
	for (auto it = career.begin(); it != career.end(); it++)
	{
		if ((*it).m_carrnum == carrinfo.m_carrnum)
		{
			(*it).m_last_gift = GetANormalDistributionNumber<ushrt>((*it).m_gift, (*it).m_gift_variance);
			(*it).m_last_wlth = GetANormalDistributionNumber<ushrt>((*it).m_wealth, (*it).m_wlth_variance);
		}
	}
}
std::string GetCareerName(uint carrnum)
{
	using namespace std;
	for (auto it = career.begin(); it != career.end(); it++)
	{
		if ((*it).m_carrnum == carrnum)
		{
			return (*it).m_carrname;
		}
	}
	return "CAREER_NAME ERRO";
}